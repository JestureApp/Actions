#include "actions/dispatcher.h"

#include "absl/status/status.h"
#include "actions/connection.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

namespace actions {

absl::StatusOr<Dispatcher> Dispatcher::Create(
    std::unique_ptr<Connection> conn) noexcept {
    Dispatcher dispatcher(std::move(conn));

    absl::Status status = dispatcher.Start();

    if (!status.ok()) return status;

    return dispatcher;
}

std::future<absl::Status> all(
    std::vector<std::future<absl::Status>>&& futures) noexcept {
    return std::async(
        std::launch::deferred,
        [](std::vector<std::future<absl::Status>> futures) {
            for (std::future<absl::Status>& fut : futures) {
                absl::Status status = fut.get();

                if (!status.ok()) return status;
            }

            return absl::OkStatus();
        },
        std::move(futures));
}

Dispatcher::Dispatcher(std::unique_ptr<Connection> conn) noexcept
    : conn(std::move(conn)), abort_requested(false), thread_running(false) {}

Dispatcher::~Dispatcher() noexcept { Stop(); }

Dispatcher::Dispatcher(Dispatcher&& other) noexcept
    : abort_requested(false), thread_running(false) {
    bool was_running = other.thread_running.load();

    other.Stop();

    conn = std::move(other.conn);
    promises = std::move(other.promises);

    // CHECKME: is this the best way to do this?
    if (was_running) assert(Start().ok());
    // assert(Start().ok());
}

Dispatcher& Dispatcher::operator=(Dispatcher&& other) noexcept {
    Stop();

    bool was_running = other.thread_running.load();

    other.Stop();

    conn = std::move(other.conn);
    promises = std::move(other.promises);

    // CHECKME: is this the best way to do this?
    if (was_running) assert(Start().ok());

    return *this;
}

absl::Status Dispatcher::Start() noexcept {
    try {
        thread_running.store(true);
        thread = std::thread(&Dispatcher::Loop, this);
    } catch (...) {
        return absl::UnknownError("Failed to start dispatcher thread");
    }

    return absl::OkStatus();
}

void Dispatcher::Stop() noexcept {
    abort_requested.store(true);

    // TODO: find way to forcefully abort.

    if (thread.joinable()) thread.join();
}

std::future<absl::Status> Dispatcher::SendKeystroke(
    Keystroke& keystroke) noexcept {
    std::unique_ptr<Promise<absl::Status>> prom =
        conn->SendKeystroke(keystroke);

    std::future<absl::Status> fut = prom->get_future();

    AddPromise(std::move(prom));

    return fut;
}

std::future<absl::Status> Dispatcher::SendKeystrokes(
    Keystrokes& keystrokes) noexcept {
    std::vector<std::future<absl::Status>> futures(keystrokes.size());

    for (Keystroke& ks : keystrokes) {
        futures.push_back(SendKeystroke(ks));
    }

    return all(std::move(futures));
}

void Dispatcher::AddPromise(std::unique_ptr<Promise<absl::Status>> prom) {
    std::unique_lock<std::mutex> lk(promises_mutex);

    promises.push_back(std::move(prom));

    // promises_cv.notify_one();
}

void Dispatcher::Loop() noexcept {
    while (!abort_requested.load()) {
        {
            {
                std::unique_lock<std::mutex> lk(promises_mutex);
                // while (promises.empty() && !abort_requested.load()) {
                //     promises_cv.wait(lk);
                // }

                if (promises.empty()) continue;

                promises.remove_if([](auto& prom) { return prom->Poll(); });
            }

            std::this_thread::yield();
        }
    }

    thread_running.store(false);
}

}  // namespace actions
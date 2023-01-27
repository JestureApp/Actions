#include "actions/dispatcher.h"

#include "absl/status/status.h"
#include "actions/connection.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

namespace actions {

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
    : thread(new std::thread(&Dispatcher::Loop, this)), conn(std::move(conn)) {}

Dispatcher::Dispatcher(Dispatcher&& other) noexcept
    : conn(std::move(other.conn)), promises(std::move(other.promises)) {}

Dispatcher& Dispatcher::operator=(Dispatcher&& other) noexcept {
    conn = std::move(other.conn);
    promises = std::move(other.promises);

    return *this;
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
    promises.push_back(std::move(prom));
}

void Dispatcher::Loop() {
    // TODO: locking
    while (true) {
        // TODO: If empty wait for new data

        promises.remove_if(&Promise<absl::Status>::poll);

        std::this_thread::yield();
    }
}

}  // namespace actions
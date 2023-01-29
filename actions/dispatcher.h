#ifndef __H_DISPATCHER__
#define __H_DISPATCHER__

#include <future>
#include <list>
#include <type_traits>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/connection.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

namespace actions {
class Dispatcher {
   public:
    static absl::StatusOr<Dispatcher> Create();
    static absl::StatusOr<Dispatcher> Create(
        std::unique_ptr<Connection>) noexcept;

    ~Dispatcher() noexcept;

    Dispatcher(Dispatcher&) = delete;
    Dispatcher& operator=(Dispatcher&) = delete;

    Dispatcher(Dispatcher&&) noexcept;
    Dispatcher& operator=(Dispatcher&&) noexcept;

    std::future<absl::Status> SendKeystroke(Keystroke& keystroke) noexcept;

    std::future<absl::Status> SendKeystrokes(Keystrokes& keystrokes) noexcept;

   private:
    Dispatcher(std::unique_ptr<Connection> conn) noexcept;

    absl::Status Start() noexcept;
    void Stop() noexcept;
    void Loop() noexcept;

    void AddPromise(std::unique_ptr<Promise<absl::Status>>);

    std::unique_ptr<Connection> conn;
    std::list<std::unique_ptr<Promise<absl::Status>>> promises;

    std::thread thread;
    std::mutex promises_mutex;
    // std::condition_variable promises_cv;
    std::atomic_bool abort_requested;
    std::atomic_bool thread_running;
};
}  // namespace actions

#endif  // __H_DISPATCHER__
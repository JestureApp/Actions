#ifndef __H_DISPATCHER__
#define __H_DISPATCHER__

#include <future>
#include <list>
#include <type_traits>

#include "absl/status/status.h"
#include "actions/connection.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

namespace actions {
class Dispatcher {
   public:
    Dispatcher(std::unique_ptr<Connection> conn) noexcept;

    Dispatcher(Dispatcher&) = delete;
    Dispatcher& operator=(Dispatcher&) = delete;

    Dispatcher(Dispatcher&&) noexcept;
    Dispatcher& operator=(Dispatcher&&) noexcept;

    std::future<absl::Status> SendKeystroke(Keystroke& keystroke) noexcept;

    std::future<absl::Status> SendKeystrokes(Keystrokes& keystrokes) noexcept;

   private:
    void AddPromise(std::unique_ptr<Promise<absl::Status>>);

    void Loop();

    std::unique_ptr<std::thread> thread;
    std::unique_ptr<Connection> conn;
    std::list<std::unique_ptr<Promise<absl::Status>>> promises;
};
}  // namespace actions

#endif  // __H_DISPATCHER__
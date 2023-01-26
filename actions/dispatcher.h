#ifndef __H_DISPATCHER__
#define __H_DISPATCHER__

#include <future>
#include <list>
#include <type_traits>

#include "absl/status/status.h"
#include "actions/connection.h"
#include "actions/promise.h"

namespace actions {
template <class Prom, class Conn>

class Dispatcher {
    static_assert(std::is_base_of<Promise, Prom>::value,
                  "Prom must inherit from Promise");

    static_assert(std::is_base_of<Connection<Prom>, Conn>::value,
                  "Conn must inherit from Connection<Prom>");

   public:
    Dispatcher(std::unique_ptr<Conn> conn);

    Dispatcher(Dispatcher& other) = delete;
    Dispatcher& operator=(Dispatcher& other) = delete;

    std::future<absl::Status> SendKeystroke(Keystroke& keystroke) noexcept {
        Prom prom = conn.SendKeystroke(keystroke);

        promises.push_back(prom);
    }

   private:
    std::unique_ptr<Conn> conn;
    std::list<Prom> promises;
};
}  // namespace actions

#endif  // __H_DISPATCHER__
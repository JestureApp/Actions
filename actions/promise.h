#ifndef __H_PROMISE__
#define __H_PROMISE__

#include <future>

#include "absl/status/status.h"

namespace actions {
template <typename Res>
class Promise {
   public:
    Promise() {}

    Promise(Promise&) = delete;
    Promise& operator=(Promise&) = delete;

    virtual bool poll() noexcept = 0;

    std::future<Res> get_future() { return prom.get_future(); }

   protected:
    void set_value(const Res& value) { prom.set_value(value); }

    void set_value(Res&& value) { prom.set_value(std::move(value)); }

   private:
    std::promise<Res> prom;
};
}  // namespace actions

#endif  // __H_PROMISE__
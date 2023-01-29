#ifndef __H_PROMISE__
#define __H_PROMISE__

#include <future>

#include "absl/status/status.h"

namespace actions {
// TODO: make promises cancellable.

template <typename Res>
class Promise {
   public:
    Promise() {}

    virtual ~Promise() {}

    Promise(Promise&) = delete;
    Promise& operator=(Promise&) = delete;

    Promise(Promise&& other) noexcept : prom(std::move(other.prom)) {}
    Promise& operator=(Promise&& other) noexcept {
        prom = std::move(other.prom);
        return *this;
    }

    virtual bool Poll() noexcept = 0;

    std::future<Res> get_future() { return prom.get_future(); }

   protected:
    void set_value(const Res& value) { prom.set_value(value); }

    void set_value(Res&& value) { prom.set_value(std::move(value)); }

   private:
    std::promise<Res> prom;
};
}  // namespace actions

#endif  // __H_PROMISE__
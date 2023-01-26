#ifndef __H_PROMISE__
#define __H_PROMISE__

#include <future>

#include "absl/status/status.h"

namespace actions {
class Promise {
   public:
    virtual bool poll() noexcept = 0;

    std::future<absl::Status> get_future() { return prom.get_future(); }

   protected:
    void set_value(const absl::Status& value) { prom.set_value(value); }

    void set_value(absl::Status&& value) { prom.set_value(std::move(value)); }

   private:
    std::promise<absl::Status> prom;
};
}  // namespace actions

#endif  // __H_PROMISE__
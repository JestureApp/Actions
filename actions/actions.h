#ifndef __H_ACTIONS__
#define __H_ACTIONS__

#include <future>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/utility/utility.h"
#include "actions/dispatcher.h"
#include "actions/keystroke.h"

namespace actions {

using Action = absl::variant<Keystrokes>;

class Actions {
   public:
    static absl::StatusOr<std::shared_ptr<Actions>> Create();

    static absl::StatusOr<std::shared_ptr<Actions>> Create(
        std::unique_ptr<Dispatcher>);

    ~Actions();

    std::future<absl::Status> Perform(Action& action);

   private:
    Actions();

    std::unique_ptr<Dispatcher> dispatcher;
};

}  // namespace actions

#endif  // __H_ACTIONS__
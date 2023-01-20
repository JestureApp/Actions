#include "actions/actions.h"

#include <future>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/dispatcher.h"
#include "actions/keystroke.h"

namespace actions {
Actions::Actions(){};

absl::StatusOr<std::shared_ptr<Actions>> Actions::Create() {
    absl::StatusOr<std::unique_ptr<Dispatcher>> dispatcher =
        Dispatcher::Create();

    if (!dispatcher.ok()) {
        return dispatcher.status();
    }

    return Actions::Create(std::move(dispatcher).value());
};

absl::StatusOr<std::shared_ptr<Actions>> Actions::Create(
    std::unique_ptr<Dispatcher> dispatcher) {
    Actions* actions = new Actions();
    actions->dispatcher = std::move(dispatcher);

    return std::shared_ptr<Actions>(actions);
}

std::future<absl::Status> Actions::Perform(Action& action) {
    if (absl::holds_alternative<Keystrokes>(action)) {
        return dispatcher->SendKeystrokes(absl::get<Keystrokes>(action));
    }

    std::promise<absl::Status> prom;
    prom.set_value(absl::UnimplementedError("Action not implemented."));

    // CHECKME: will the promises deconstruction cause problems?
    return prom.get_future();
}

}  // namespace actions
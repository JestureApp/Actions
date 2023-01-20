#include "actions/linux/dispatcher.h"

#include <future>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/dispatcher_base.h"
#include "actions/keystroke.h"

namespace actions {
absl::StatusOr<std::unique_ptr<LinuxDispatcher>> LinuxDispatcher::Create() {
    return absl::UnimplementedError("Not Implemented");
}

std::future<absl::Status> LinuxDispatcher::SendKeystrokes(
    Keystrokes &keystrokes) {
    std::promise<absl::Status> prom;
    prom.set_value(absl::UnimplementedError("Action not implemented."));

    // CHECKME: will the promises deconstruction cause problems?
    return prom.get_future();
}
}  // namespace actions
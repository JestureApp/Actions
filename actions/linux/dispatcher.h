#ifndef __H_LINUX_DISPATCHER__
#define __H_LINUX_DISPATCHER__

#include <future>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/dispatcher_base.h"
#include "actions/keystroke.h"

namespace actions {
class LinuxDispatcher : public DispatcherBase {
   public:
    static absl::StatusOr<std::unique_ptr<LinuxDispatcher>> Create();

    std::future<absl::Status> SendKeystrokes(Keystrokes& keystrokes) override;
};
}  // namespace actions

#endif  // __H_LINUX_DISPATCHER__
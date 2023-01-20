#ifndef __H_LINUX_DISPATCHER__
#define __H_LINUX_DISPATCHER__

#include <future>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/dispatcher_base.h"
#include "actions/keystroke.h"
#include "actions/linux/xcb_connection.h"

namespace actions {
class LinuxDispatcher : public DispatcherBase {
   public:
    static absl::StatusOr<LinuxDispatcher> Create();

    LinuxDispatcher(LinuxDispatcher& other) = delete;
    LinuxDispatcher& operator=(LinuxDispatcher& other) = delete;

    LinuxDispatcher(LinuxDispatcher&& other) noexcept;
    LinuxDispatcher& operator=(LinuxDispatcher&& other) noexcept;

    std::future<absl::Status> SendKeystrokes(Keystrokes& keystrokes) override;

   private:
    LinuxDispatcher(XcbConnection&& conn);

    XcbConnection conn;
};
}  // namespace actions

#endif  // __H_LINUX_DISPATCHER__
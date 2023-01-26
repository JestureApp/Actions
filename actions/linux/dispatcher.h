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
    /**
     * Creates a new dispatcher.
     *
     * @return A `absl::Status` in the case of a failure or an `LinuxDispatcher`
     * in the case of a success.
     */
    static absl::StatusOr<LinuxDispatcher> Create() noexcept;

    LinuxDispatcher(std::unique_ptr<XcbConnection> conn) noexcept;

    LinuxDispatcher(LinuxDispatcher& other) = delete;
    LinuxDispatcher& operator=(LinuxDispatcher& other) = delete;

    LinuxDispatcher(LinuxDispatcher&& other) noexcept;
    LinuxDispatcher& operator=(LinuxDispatcher&& other) noexcept;

    /**
     * Sends a sequence of keystrokes to the focused window.
     *
     * @param keystrokes The keystrokes to send.
     *
     * @return A future that resolves upon an error or the completion of the
     * action. In the event of an error that status will not be
     * `absl::OkStatus()`.
     */
    std::future<absl::Status> SendKeystrokes(Keystrokes&& keystrokes) override;

   private:
    std::unique_ptr<XcbConnection> conn;
};
}  // namespace actions

#endif  // __H_LINUX_DISPATCHER__
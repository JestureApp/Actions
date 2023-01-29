#ifndef __H_CONNECTION__
#define __H_CONNECTION__

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

namespace actions {
class Connection {
   public:
    static absl::StatusOr<std::unique_ptr<Connection>> Create() noexcept;

    /**
     * Sends a sequence of keystroke events to the focused window
     *
     * @param keystrokes    The sequence of keystrokes to send as events to the
     *                      focused window.
     *
     * @return  A future that resolves either when the keystrokes were
     * performed, or when there was an error. In the case of a success the
     * future will resolve to `absl::OkStatus`. In the case of an error the
     * future will resolve to an error status.
     */
    virtual std::unique_ptr<Promise<absl::Status>> SendKeystroke(
        Keystroke& keystroke) noexcept = 0;

    virtual ~Connection(){};
};
}  // namespace actions

#endif  // __H_CONNECTION_
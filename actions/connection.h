#ifndef __H_CONNECTION__
#define __H_CONNECTION__

#include "absl/status/status.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

namespace actions {
template <class Prom>
class Connection {
   public:
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
    virtual Prom SendKeystroke(Keystroke& keystroke) noexcept = 0;
};
}  // namespace actions

#endif  // __H_CONNECTION_
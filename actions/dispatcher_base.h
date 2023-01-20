#ifndef __H_DISPATCHER_BASE__
#define __H_DISPATCHER_BASE__

#include <future>
#include <type_traits>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/keystroke.h"

namespace actions {
class DispatcherBase {
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
    virtual std::future<absl::Status> SendKeystrokes(
        Keystrokes& keystrokes) = 0;
};
}  // namespace actions

#define CHECK_DISPATCHER_IMPL(Disp)                                      \
    static_assert(std::is_base_of<actions::DispatcherBase, Disp>::value, \
                  "Dispatcher must inherit from "                        \
                  "DispatcherBase");                                     \
    static_assert(!std::is_abstract<Disp>::value,                        \
                  "Dispatcher must implement "                           \
                  "all virtual methods");

#endif  // __H_DISPATCHER_BASE__
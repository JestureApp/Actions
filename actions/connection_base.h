#ifndef __H_CONNECTION_BASE__
#define __H_CONNECTION_BASE__

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/keystroke.h"
#include "type_traits"

namespace actions {
class ConnectionBase {
   public:
    virtual absl::Status SendKeystroke(Keystrokes& keystroke) = 0;
};

}  // namespace actions

// TODO: ensure connection implements Open
#define CHECK_CONNECTION_IMPL(Conn)                                      \
    static_assert(std::is_base_of<actions::ConnectionBase, Conn>::value, \
                  "Connection must inherit from ConnectionBase");        \
    static_assert(!std::is_abstract<Conn>::value,                        \
                  "Connection must not be abstract");

#endif  // __H_CONNECTION_BASE__
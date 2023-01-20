#ifndef __H_LINUX_XCB_CONNECTION__
#define __H_LINUX_XCB_CONNECTION__

#include <xcb/xcb.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace actions {
class XcbConnection {
   public:
    static absl::StatusOr<XcbConnection> Open();

    ~XcbConnection();

    XcbConnection(XcbConnection& other) = delete;
    XcbConnection& operator=(XcbConnection& other) = delete;

    XcbConnection(XcbConnection&& other) noexcept;
    XcbConnection& operator=(XcbConnection&& other) noexcept;

   private:
    XcbConnection(xcb_connection_t* conn);

    xcb_connection_t* conn;
};
}  // namespace actions
#endif
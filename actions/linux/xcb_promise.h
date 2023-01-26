#ifndef __H_LINUX_XCB_PROMISE__
#define __H_LINUX_XCB_PROMISE__

#include <xcb/xcb.h>
#include <xcb/xcbext.h>

#include "absl/status/status.h"
#include "actions/promise.h"

namespace actions {
class XcbPromise : public Promise {
   public:
    XcbPromise(xcb_connection_t *, unsigned int);

    XcbPromise(xcb_connection_t *, xcb_void_cookie_t);

    bool poll() noexcept override;

   private:
    void handle_error(xcb_generic_error_t *_error);

    xcb_connection_t *conn;
    unsigned int seqnum;
};
}  // namespace actions

#endif  // __H_LINUX_XCB_PROMISE
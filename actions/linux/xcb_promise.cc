#include "actions/linux/xcb_promise.h"

#include <xcb/xcb.h>
#include <xcb/xcbext.h>

#include "absl/status/status.h"

namespace actions {
XcbPromise::XcbPromise(xcb_connection_t *conn, unsigned int seqnum)
    : conn(conn), seqnum(seqnum) {}

XcbPromise::XcbPromise(xcb_connection_t *conn, xcb_void_cookie_t cookie)
    : conn(conn), seqnum(cookie.sequence) {}

bool XcbPromise::poll() noexcept {
    void *reply = nullptr;
    xcb_generic_error_t *error = nullptr;

    if (xcb_poll_for_reply(conn, seqnum, &reply, &error)) {
        if (error)
            handle_error(error);
        else
            set_value(absl::OkStatus());

        return true;
    }

    return false;
}

void XcbPromise::handle_error(xcb_generic_error_t *_error) {
    // TODO: better error message
    set_value(absl::InternalError("Request failed"));
}

}  // namespace actions
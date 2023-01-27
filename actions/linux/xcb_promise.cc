#include "actions/linux/xcb_promise.h"

#include <xcb/xcb.h>
#include <xcb/xcbext.h>

#include "absl/status/status.h"

namespace actions {
XcbPromise::XcbPromise(xcb_connection_t *conn,
                       std::list<unsigned int> &&seqnums)
    : conn(conn), seqnums(std::move(seqnums)) {}

XcbPromise::XcbPromise(XcbPromise &&other) noexcept {
    conn = other.conn;
    other.conn = nullptr;

    seqnums = std::move(other.seqnums);
}

XcbPromise &XcbPromise::operator=(XcbPromise &&other) noexcept {
    conn = other.conn;
    other.conn = nullptr;

    seqnums = std::move(other.seqnums);

    return *this;
}

bool XcbPromise::poll() noexcept {
    seqnums.remove_if([this](unsigned int seqnum) {
        void *reply = nullptr;

        bool has_reply = xcb_poll_for_reply(conn, seqnum, &reply, &error);

        if (error) {
            handle_error(error);

            return true;
        }

        return has_reply;
    });

    if (error) seqnums.clear();

    return seqnums.empty();
}

void XcbPromise::handle_error(xcb_generic_error_t *_error) {
    // TODO: better error message
    set_value(absl::InternalError("Request failed"));
}
}  // namespace actions
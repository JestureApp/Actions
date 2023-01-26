#include "actions/linux/xcb_connection.h"

#include <absl/status/internal/statusor_internal.h>
#include <absl/status/status.h>
#include <xcb/xcb.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace actions {
XcbConnection::XcbConnection(xcb_connection_t* conn) : conn(conn) {}

XcbConnection::~XcbConnection() { xcb_disconnect(conn); }

XcbConnection::XcbConnection(XcbConnection&& other) noexcept {
    conn = other.conn;

    other.conn = nullptr;
}

XcbConnection& XcbConnection::operator=(XcbConnection&& other) noexcept {
    conn = other.conn;

    other.conn = nullptr;

    return *this;
}

absl::StatusOr<XcbConnection> XcbConnection::Open() {
    int _screen_num;
    xcb_connection_t* conn = xcb_connect(nullptr, &_screen_num);

    if (conn == nullptr)
        return absl::UnavailableError("Could not connected to X server");

    return XcbConnection(conn);
}

}  // namespace actions
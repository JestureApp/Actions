#include "actions/linux/xcb_connection.h"

#include <absl/status/internal/statusor_internal.h>
#include <absl/status/status.h>
#include <xcb/xcb.h>
#include <xcb/xtest.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/linux/xcb_promise.h"
#include "actions/promise.h"

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

std::unique_ptr<Promise<absl::Status>> XcbConnection::SendKeystroke(
    Keystroke& keystroke) noexcept {
    std::list<unsigned int> seqnums;

    seqnums.push_back(
        xcb_test_fake_input_checked(conn, XCB_KEY_PRESS, 0, 0, 0, 0, 0, 0)
            .sequence);

    seqnums.push_back(
        xcb_test_fake_input_checked(conn, XCB_KEY_RELEASE, 0, 0, 0, 0, 0, 0)
            .sequence);

    return std::make_unique<XcbPromise>(conn, std::move(seqnums));
}

}  // namespace actions
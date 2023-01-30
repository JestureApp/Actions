#include "actions/linux/xcb_connection.h"

#include <xcb/xcb.h>
#include <xcb/xtest.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/linux/xcb_error.h"
#include "actions/linux/xcb_promise.h"
#include "actions/promise.h"

namespace actions {

XcbConnection::XcbConnection(xcb_connection_t* conn, xcb_screen_t* screen,
                             xcb_key_symbols_t* key_symbols)
    : conn(conn), screen(screen), key_symbols(key_symbols) {}

XcbConnection::~XcbConnection() { xcb_disconnect(conn); }

XcbConnection::XcbConnection(XcbConnection&& other) noexcept {
    conn = other.conn;
    other.conn = nullptr;

    screen = other.screen;
    other.screen = nullptr;

    key_symbols = other.key_symbols;
    other.key_symbols = nullptr;
}

XcbConnection& XcbConnection::operator=(XcbConnection&& other) noexcept {
    conn = other.conn;
    other.conn = nullptr;

    screen = other.screen;
    other.screen = nullptr;

    key_symbols = other.key_symbols;
    other.key_symbols = nullptr;

    return *this;
}

// TODO: clean up
absl::StatusOr<std::unique_ptr<XcbConnection>> XcbConnection::Open() noexcept {
    absl::Status status = absl::OkStatus();
    int screen_num;
    xcb_connection_t* conn = xcb_connect(nullptr, &screen_num);

    if (conn == nullptr)
        return absl::UnavailableError("Could not connected to X server");

    status.Update(XcbError(xcb_connection_has_error(conn)));

    if (!status.ok()) {
        xcb_disconnect(conn);
        return status;
    }

    // Get the primary screen
    const xcb_setup_t* setup = xcb_get_setup(conn);
    xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(setup);

    if (xcb_setup_roots_length(setup) <= screen_num) {
        xcb_disconnect(conn);
        return absl::OutOfRangeError("Invalid Screen number");
    }

    for (int i = 0; i < screen_num; i++) xcb_screen_next(&screen_iter);

    xcb_screen_t* screen = screen_iter.data;

    // Ensure that XTest extension is present
    const xcb_query_extension_reply_t* xtest_data =
        xcb_get_extension_data(conn, &xcb_test_id);

    status.Update(XcbError(xcb_connection_has_error(conn)));

    if (!status.ok()) {
        xcb_disconnect(conn);
        return status;
    }

    if (!xtest_data->present) {
        xcb_disconnect(conn);
        return absl::UnavailableError("XTest extension not present");
    }

    // Setup key symbol translation
    xcb_key_symbols_t* key_symbols = xcb_key_symbols_alloc(conn);

    return std::unique_ptr<XcbConnection>(
        new XcbConnection(conn, screen, key_symbols));
}

std::unique_ptr<Promise<absl::Status>> XcbConnection::SendKeystroke(
    Keystroke& keystroke) noexcept {
    std::list<unsigned int> seqnums;

    uint8_t code = *xcb_key_symbols_get_keycode(key_symbols, keystroke.key);

    seqnums.push_back(xcb_test_fake_input_checked(conn, XCB_KEY_PRESS, code, 0,
                                                  screen->root, 0, 0, 0)
                          .sequence);

    seqnums.push_back(xcb_test_fake_input_checked(conn, XCB_KEY_RELEASE, code,
                                                  0, screen->root, 0, 0, 0)
                          .sequence);

    Flush();

    return std::make_unique<XcbPromise>(conn, std::move(seqnums));
}

void XcbConnection::Flush() noexcept { xcb_flush(conn); }

}  // namespace actions
#include "actions/internal/x11/xcb_connection.h"

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xtest.h>

#include <future>

#include "absl/status/status.h"
#include "absl/types/variant.h"
#include "actions/internal/util.h"
#include "actions/internal/x11/xcb_error.h"
#include "actions/internal/x11/xcb_keyboard.h"

namespace actions::internal::x11 {
absl::StatusOr<std::unique_ptr<XcbConnection>>
XcbConnection::Create() noexcept {
    // Setup connection
    absl::Status status = absl::OkStatus();
    int screen_num;
    xcb_connection_t* conn = xcb_connect(NULL, &screen_num);

    if (conn == NULL) {
        return absl::UnavailableError("Failed to open connection to X server");
    }

    status.Update(XcbStatus(xcb_connection_has_error(conn)));

    if (!status.ok()) {
        xcb_disconnect(conn);
        return status;
    }

    // Get primary screen
    const xcb_setup_t* setup = xcb_get_setup(conn);
    xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(setup);

    if (xcb_setup_roots_length(setup) <= screen_num) {
        xcb_disconnect(conn);
        return absl::OutOfRangeError("Invalid screen number");
    }

    for (int i = 0; i < screen_num; i++) {
        xcb_screen_next(&screen_iter);
    }

    xcb_screen_t* screen = screen_iter.data;

    // Ensure necessary extensions are present
    const xcb_query_extension_reply_t* xtest_data =
        xcb_get_extension_data(conn, &xcb_test_id);

    status.Update(XcbStatus(xcb_connection_has_error(conn)));

    if (!status.ok()) {
        xcb_disconnect(conn);
        return status;
    }

    if (!xtest_data->present) {
        xcb_disconnect(conn);
        return absl::UnavailableError("XTest extension not present");
    }

    // Construct keyboard
    XcbKeyboard keyboard(conn);

    return std::unique_ptr<XcbConnection>(
        new XcbConnection(conn, screen, std::move(keyboard)));
}

XcbConnection::XcbConnection(xcb_connection_t* conn, xcb_screen_t* screen,
                             XcbKeyboard&& keyboard) noexcept
    : conn(conn), screen(screen), keyboard(std::move(keyboard)) {}

XcbConnection::~XcbConnection() noexcept { xcb_disconnect(conn); }

XcbConnection::XcbConnection(XcbConnection&& other) noexcept
    : keyboard(std::move(other.keyboard)) {
    conn = other.conn;
    other.conn = nullptr;

    screen = other.screen;
    other.screen = nullptr;
}

XcbConnection& XcbConnection::operator=(XcbConnection&& other) noexcept {
    if (this != &other) {
        keyboard = std::move(other.keyboard);

        conn = other.conn;
        other.conn = nullptr;

        screen = other.screen;
        other.screen = nullptr;
    }

    return *this;
}

std::future<absl::Status> XcbConnection::Keystroke(
    const action::Keystroke& keystroke, const action::Target& target) noexcept {
    xcb_window_t root;

    if (absl::holds_alternative<action::target::Focused>(target)) {
        root = screen->root;
    } else {
        return util::Resolve(absl::UnimplementedError("Not Implemented."));
    }

    return keyboard.Keystroke(keystroke, root);
}

std::future<absl::Status> XcbConnection::KeysPress(
    const action::KeysPress& keys_press,
    const action::Target& target) noexcept {
    xcb_window_t root;

    if (absl::holds_alternative<action::target::Focused>(target)) {
        root = screen->root;
    } else {
        return util::Resolve(absl::UnimplementedError("Not Implemented."));
    }

    return keyboard.KeysPress(keys_press, root);
}

std::future<absl::Status> XcbConnection::KeysRelease(
    const action::KeysRelease& keys_release,
    const action::Target& target) noexcept {
    xcb_window_t root;

    if (absl::holds_alternative<action::target::Focused>(target)) {
        root = screen->root;
    } else {
        return util::Resolve(absl::UnimplementedError("Not Implemented."));
    }

    return keyboard.KeysRelease(keys_release, root);
}

std::future<absl::Status> XcbConnection::MoveCursor(
    const action::CursorMove& cursor_move,
    const action::Target& target) noexcept {
    // TODO: get size of window to properly scale coordinates

    xcb_window_t dest_window;

    if (absl::holds_alternative<action::target::Focused>(target)) {
        dest_window = screen->root;
    } else {
        return util::Resolve(absl::UnimplementedError("Not Implemented."));
    }

    return std::async(std::launch::deferred, [=]() {
        int16_t src_x = 0;
        int16_t src_y = 0;

        if (cursor_move.relative) {
            auto pointer_loc = QueryPointer().get();

            if (!pointer_loc.ok()) return pointer_loc.status();

            src_x = pointer_loc.value()->root_x;
            src_y = pointer_loc.value()->root_y;
        }

        auto geometry = GetWindowGeometry(dest_window).get();

        if (!geometry.ok()) return geometry.status();

        auto dest_width = geometry.value()->width;
        auto dest_height = geometry.value()->height;

        auto x = cursor_move.x * dest_width + src_x;
        auto y = cursor_move.y * dest_height + src_y;

        xcb_void_cookie_t cookie = xcb_warp_pointer_checked(
            conn, XCB_NONE, dest_window, 0, 0, 0, 0, x, y);

        xcb_flush(conn);

        return CheckCookie(cookie).get();
    });
}

std::future<absl::Status> XcbConnection::MousePress(
    const action::MousePress& mouse_press,
    const action::Target& _target) noexcept {
    xcb_button_index_t button;

    switch (mouse_press) {
        case action::MousePress::LeftPress:
            button = XCB_BUTTON_INDEX_1;
            break;
        case action::MousePress::RightPress:
            button = XCB_BUTTON_INDEX_2;
            break;
        case action::MousePress::MiddlePress:
            button = XCB_BUTTON_INDEX_3;
            break;
        default:
            return util::Resolve(absl::UnimplementedError("Not implemented"));
    }

    return SendMouseInput(button, true);
}

std::future<absl::Status> XcbConnection::MouseRelease(
    const action::MouseRelease& mouse_release,
    const action::Target& target) noexcept {
    xcb_button_index_t button;

    switch (mouse_release) {
        case action::MouseRelease::LeftRelease:
            button = XCB_BUTTON_INDEX_1;
            break;
        case action::MouseRelease::RightRelease:
            button = XCB_BUTTON_INDEX_2;
            break;
        case action::MouseRelease::MiddleRelease:
            button = XCB_BUTTON_INDEX_3;
            break;
        default:
            return util::Resolve(absl::UnimplementedError("Not implemented"));
    }

    return SendMouseInput(button, false);
}

std::future<absl::Status> XcbConnection::MouseClick(
    const action::MouseClick& mouse_click,
    const action::Target& target) noexcept {
    xcb_button_index_t button;

    switch (mouse_click) {
        case action::MouseClick::LeftClick:
            button = XCB_BUTTON_INDEX_1;
            break;
        case action::MouseClick::RightClick:
            button = XCB_BUTTON_INDEX_2;
            break;
        case action::MouseClick::MiddleClick:
            button = XCB_BUTTON_INDEX_3;
            break;
        default:
            return util::Resolve(absl::UnimplementedError("Not implemented"));
    }

    return SendMouseClick(button);
}

std::future<XcbReply<xcb_get_window_attributes_reply_t>>
XcbConnection::GetWindowAttributes(xcb_window_t window) {
    xcb_get_window_attributes_cookie_t cookie =
        xcb_get_window_attributes(conn, window);

    xcb_flush(conn);

    return ResolveReply<xcb_get_window_attributes_reply_t,
                        xcb_get_window_attributes_cookie_t>(
        cookie, xcb_get_window_attributes_reply);
}

std::future<XcbReply<xcb_get_geometry_reply_t>>
XcbConnection::GetWindowGeometry(xcb_window_t window) {
    xcb_get_geometry_cookie_t cookie = xcb_get_geometry(conn, window);

    xcb_flush(conn);

    return ResolveReply<xcb_get_geometry_reply_t, xcb_get_geometry_cookie_t>(
        cookie, xcb_get_geometry_reply);
}

std::future<XcbReply<xcb_query_pointer_reply_t>> XcbConnection::QueryPointer() {
    xcb_query_pointer_cookie_t cookie = xcb_query_pointer(conn, screen->root);

    xcb_flush(conn);

    return ResolveReply<xcb_query_pointer_reply_t, xcb_query_pointer_cookie_t>(
        cookie, xcb_query_pointer_reply);
}

std::future<absl::Status> XcbConnection::SendMouseClick(
    xcb_button_index_t button) {
    return std::async(std::launch::deferred, [=]() {
        auto status = SendMouseInput(button, true).get();

        if (!status.ok()) return status;

        return SendMouseInput(button, false).get();
    });
}

std::future<absl::Status> XcbConnection::SendMouseInput(
    xcb_button_index_t button, bool press) {
    return SendFakeInput(press ? XCB_BUTTON_PRESS : XCB_BUTTON_RELEASE, button);
}

std::future<absl::Status> XcbConnection::SendFakeInput(uint8_t type,
                                                       uint8_t detail) {
    xcb_void_cookie_t cookie = xcb_test_fake_input_checked(
        conn, type, detail, 0, screen->root, 0, 0, 0);

    xcb_flush(conn);

    return CheckCookie(cookie);
}

std::future<absl::Status> XcbConnection::CheckCookie(xcb_void_cookie_t cookie) {
    return std::async(std::launch::deferred, [this, cookie]() {
        xcb_generic_error_t* error = xcb_request_check(conn, cookie);

        if (error) {
            return XcbErrorToStatus(conn, error);
        }

        return absl::OkStatus();
    });
}

}  // namespace actions::internal::x11
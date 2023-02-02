#include "actions/internal/linux/xcb_keyboard.h"

#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xtest.h>

#include <future>
#include <unordered_set>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/action/keystroke.h"
#include "actions/internal/linux/xcb_error.h"
#include "actions/internal/util.h"

namespace actions::internal::linux {

XcbKeyboard::XcbKeyboard(xcb_connection_t* conn) noexcept
    : conn(conn), key_symbols(xcb_key_symbols_alloc(conn)) {}

XcbKeyboard::~XcbKeyboard() noexcept { xcb_key_symbols_free(key_symbols); }

XcbKeyboard::XcbKeyboard(XcbKeyboard&& other) noexcept {
    conn = other.conn;
    other.conn = nullptr;

    key_symbols = other.key_symbols;
    other.key_symbols = nullptr;
}

XcbKeyboard& XcbKeyboard::operator=(XcbKeyboard&& other) noexcept {
    if (this != &other) {
        conn = other.conn;
        other.conn = nullptr;

        key_symbols = other.key_symbols;
        other.key_symbols = nullptr;
    }

    return *this;
}

std::future<absl::Status> XcbKeyboard::SendKeystrokes(
    const action::Keystroke& keystroke, xcb_window_t root) noexcept {
    std::vector<std::future<absl::Status>> futures;
    futures.reserve(keystroke.size() * 2);

    for (xcb_keysym_t key : keystroke) {
        futures.push_back(SendKey(true, key, root));
    }

    for (xcb_keysym_t key : keystroke) {
        futures.push_back(SendKey(false, key, root));
    }

    return util::AllOk(std::move(futures));
}

std::future<absl::Status> XcbKeyboard::SendKey(bool press, xcb_keysym_t key,
                                               xcb_window_t root) noexcept {
    return std::async(std::launch::deferred, [=]() {
        xcb_keycode_t* codes = xcb_key_symbols_get_keycode(key_symbols, key);

        if (!codes) return absl::InternalError("Unknown key symbol");

        xcb_keycode_t code = codes[0];

        free(codes);

        return SendFakeInput(press ? XCB_KEY_PRESS : XCB_KEY_RELEASE, code,
                             root)
            .get();
    });
}

std::future<absl::Status> XcbKeyboard::SendFakeInput(
    uint8_t type, uint8_t detail, xcb_window_t root) noexcept {
    // Send as soon as possible
    xcb_void_cookie_t cookie =
        xcb_test_fake_input_checked(conn, type, detail, 0, root, 0, 0, 0);

    xcb_flush(conn);

    return std::async(std::launch::deferred, [=]() {
        xcb_generic_error_t* error = xcb_request_check(conn, cookie);

        if (error) {
            return XcbErrorToStatus(conn, error);
        }

        return absl::OkStatus();
    });
}

}  // namespace actions::internal::linux
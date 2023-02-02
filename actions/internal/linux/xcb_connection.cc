#include "actions/internal/linux/xcb_connection.h"

#include <xcb/xcb.h>

#include <future>

#include "absl/status/status.h"

namespace actions::internal::linux {
XcbConnection::XcbConnection(xcb_connection_t* conn,
                             XcbKeyboard&& keyboard) noexcept
    : conn(conn), keyboard(std::move(keyboard)) {}

XcbConnection::~XcbConnection() noexcept { xcb_disconnect(conn); }

XcbConnection::XcbConnection(XcbConnection&& other) noexcept
    : keyboard(std::move(other.keyboard)) {
    conn = other.conn;
    other.conn = nullptr;
}

XcbConnection& XcbConnection::operator=(XcbConnection&& other) noexcept {
    if (this != &other) {
        keyboard = std::move(other.keyboard);

        conn = other.conn;
        other.conn = nullptr;
    }

    return *this;
}

std::future<absl::Status> XcbConnection::SendKeystroke(
    const action::Keystroke& keystroke, const action::Target& target) noexcept {
    // TODO: determine root window id.

    return keyboard.SendKeystrokes(keystroke, 0);
}
}  // namespace actions::internal::linux
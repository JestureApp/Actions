#ifndef ACTIONS_INTERNAL_LINUX_XCB_CONNECTION_H
#define ACTIONS_INTERNAL_LINUX_XCB_CONNECTION_H

#include <xcb/xcb.h>

#include <future>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/internal/connection.h"
#include "actions/internal/linux/xcb_keyboard.h"

namespace actions::internal::linux {

class XcbConnection : public Connection {
   private:
    xcb_connection_t* conn;
    xcb_screen_t* screen;
    XcbKeyboard keyboard;

   public:
    static absl::StatusOr<std::unique_ptr<XcbConnection>> Create() noexcept;

    XcbConnection(xcb_connection_t* conn, xcb_screen_t* screen,
                  XcbKeyboard&& keyboard) noexcept;
    ~XcbConnection() noexcept;

    XcbConnection(XcbConnection&) = delete;
    XcbConnection& operator=(XcbConnection&) = delete;

    XcbConnection(XcbConnection&&) noexcept;
    XcbConnection& operator=(XcbConnection&&) noexcept;

    std::future<absl::Status> SendKeystroke(
        const action::Keystroke& keystroke,
        const action::Target& target) noexcept override;
};

}  // namespace actions::internal::linux

#endif  // ACTIONS_INTERNAL_LINUX_XCB_CONNECTION_H
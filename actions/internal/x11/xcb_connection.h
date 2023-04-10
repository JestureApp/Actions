#ifndef ACTIONS_INTERNAL_X11_XCB_CONNECTION_H
#define ACTIONS_INTERNAL_X11_XCB_CONNECTION_H

#include <xcb/xcb.h>

#include <future>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/internal/connection.h"
#include "actions/internal/x11/xcb_error.h"
#include "actions/internal/x11/xcb_keyboard.h"

namespace actions::internal::x11 {
template <typename T>
using XcbReply = absl::StatusOr<T*>;

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

    std::future<absl::Status> Keystroke(
        const action::Keystroke& keystroke,
        const action::Target& target) noexcept override;

    std::future<absl::Status> KeysPress(
        const action::KeysPress& keys_press,
        const action::Target& target) noexcept override;

    std::future<absl::Status> KeysRelease(
        const action::KeysRelease& keys_release,
        const action::Target& target) noexcept override;

    std::future<absl::Status> MoveCursor(
        const action::CursorMove& cursor_move,
        const action::Target& target) noexcept override;

    std::future<absl::Status> MousePress(
        const action::MousePress& mouse_press,
        const action::Target& target) noexcept override;

    std::future<absl::Status> MouseRelease(
        const action::MouseRelease& mouse_release,
        const action::Target& target) noexcept override;

    std::future<absl::Status> MouseClick(
        const action::MouseClick& mouse_click,
        const action::Target& target) noexcept override;

   private:
    std::future<XcbReply<xcb_get_window_attributes_reply_t>>
    GetWindowAttributes(xcb_window_t window);

    std::future<XcbReply<xcb_get_geometry_reply_t>> GetWindowGeometry(
        xcb_window_t window);

    std::future<XcbReply<xcb_query_pointer_reply_t>> QueryPointer();

    template <typename T, typename Cookie>
    std::future<XcbReply<T>> ResolveReply(
        Cookie cookie,
        std::function<T*(xcb_connection_t*, Cookie, xcb_generic_error_t**)>
            reply_getter) {
        return std::async(std::launch::deferred,
                          [this, cookie, reply_getter]() -> XcbReply<T> {
                              xcb_generic_error_t* error;

                              T* reply = reply_getter(conn, cookie, &error);

                              if (error) {
                                  return XcbErrorToStatus(conn, error);
                              }

                              return reply;
                          });
    }

    std::future<absl::Status> SendMouseClick(xcb_button_index_t button);

    std::future<absl::Status> SendMouseInput(xcb_button_index_t button,
                                             bool press);

    std::future<absl::Status> SendFakeInput(uint8_t type, uint8_t detail);

    std::future<absl::Status> CheckCookie(xcb_void_cookie_t cookie);
};
}  // namespace actions::internal::x11

#endif  // ACTIONS_INTERNAL_X11_XCB_CONNECTION_H
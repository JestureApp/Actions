#ifndef ACTIONS_INTERNAL_X11_XCB_KEYBOARD_H
#define ACTIONS_INTERNAL_X11_XCB_KEYBOARD_H

#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>

#include <future>
#include <map>
#include <unordered_set>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/action/keystroke.h"

namespace actions::internal::x11 {

class XcbKeyboard {
   private:
    xcb_connection_t* conn;
    xcb_key_symbols_t* key_symbols;

    std::future<absl::Status> SendKey(bool press, xcb_keysym_t key,
                                      xcb_window_t root) noexcept;

    std::future<absl::Status> SendFakeInput(uint8_t type, uint8_t detail,
                                            xcb_window_t root) noexcept;

   public:
    XcbKeyboard(xcb_connection_t* conn) noexcept;
    ~XcbKeyboard() noexcept;

    XcbKeyboard(XcbKeyboard&) = delete;
    XcbKeyboard& operator=(XcbKeyboard&) = delete;

    XcbKeyboard(XcbKeyboard&&) noexcept;
    XcbKeyboard& operator=(XcbKeyboard&&) noexcept;

    std::future<absl::Status> SendKeystrokes(const action::Keystroke& keystroke,
                                             xcb_window_t root) noexcept;
};

}  // namespace actions::internal::x11

#endif  // ACTIONS_INTERNAL_X11_XCB_KEYBOARD_H
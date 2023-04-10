#ifndef ACTIONS_INTERNAL_CONNECTION_H
#define ACTIONS_INTERNAL_CONNECTION_H

#include <future>

#include "absl/status/status.h"
#include "actions/action.h"

namespace actions::internal {

/// @brief An abstract connection to a display server.
class Connection {
   public:
    virtual ~Connection(){};

    /// @brief Sends a keystroke to the associated display server.
    /// @param keystroke The keystroke to send.
    /// @param target The target of the keystroke.
    /// @return A future which resolves to an ok status if the keystroke was
    /// successfully sent, or an error status otherwise.
    virtual std::future<absl::Status> Keystroke(
        const action::Keystroke& keystroke,
        const action::Target& target) noexcept = 0;

    virtual std::future<absl::Status> KeysPress(
        const action::KeysPress& keys_press,
        const action::Target& target) noexcept = 0;

    virtual std::future<absl::Status> KeysRelease(
        const action::KeysRelease& keys_release,
        const action::Target& target) noexcept = 0;

    virtual std::future<absl::Status> MoveCursor(
        const action::CursorMove& cursor_move,
        const action::Target& target) noexcept = 0;

    virtual std::future<absl::Status> MousePress(
        const action::MousePress& mouse_press,
        const action::Target& target) noexcept = 0;

    virtual std::future<absl::Status> MouseRelease(
        const action::MouseRelease& mouse_release,
        const action::Target& target) noexcept = 0;

    virtual std::future<absl::Status> MouseClick(
        const action::MouseClick& mouse_click,
        const action::Target& target) noexcept = 0;
};

}  // namespace actions::internal

#endif  // ACTIONS_INTERNAL_CONNECTION_H
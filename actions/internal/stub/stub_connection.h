#ifndef ACTIONS_INTERNAL_STUB_STUB_CONNECTION_H
#define ACTIONS_INTERNAL_STUB_STUB_CONNECTION_H

#include <future>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/internal/connection.h"

namespace actions::internal::stub {
class StubConnection : public Connection {
   public:
    static absl::StatusOr<std::unique_ptr<StubConnection>> Create() noexcept;

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
};
}  // namespace actions::internal::stub

#endif  // ACTIONS_INTERNAL_STUB_STUB_CONNECTION_H
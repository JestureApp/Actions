#include "actions/internal/stub/stub_connection.h"

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/internal/connection.h"
#include "actions/internal/util.h"

namespace actions::internal::stub {

absl::StatusOr<std::unique_ptr<StubConnection>>
StubConnection::Create() noexcept {
    return std::make_unique<StubConnection>();
}

std::future<absl::Status> StubConnection::SendKeystroke(
    const action::Keystroke& keystroke, const action::Target& target) noexcept {
    return util::Resolve(absl::OkStatus());
}

std::future<absl::Status> StubConnection::MoveCursor(
    const action::CursorMove& cursor_move,
    const action::Target& target) noexcept {
    return util::Resolve(absl::OkStatus());
}

std::future<absl::Status> StubConnection::MousePress(
    const action::MousePress& mouse_press,
    const action::Target& target) noexcept {
    return util::Resolve(absl::OkStatus());
}

std::future<absl::Status> StubConnection::MouseRelease(
    const action::MouseRelease& mouse_release,
    const action::Target& target) noexcept {
    return util::Resolve(absl::OkStatus());
}

std::future<absl::Status> StubConnection::MouseClick(
    const action::MouseClick& mouse_click,
    const action::Target& target) noexcept {
    return util::Resolve(absl::OkStatus());
}

}  // namespace actions::internal::stub
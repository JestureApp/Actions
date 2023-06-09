#include "actions/actions.h"

#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/internal/connection.h"
#include "actions/internal/util.h"

#if defined(__x11__)
#include "actions/internal/x11/xcb_connection.h"
#else
#include "actions/internal/stub/stub_connection.h"
#endif

namespace actions {
absl::StatusOr<Actions> Actions::Create(
    std::unique_ptr<internal::Connection> conn) noexcept {
    return Actions(std::move(conn));
}

absl::StatusOr<Actions> Actions::Create() noexcept {
#if defined(__x11__)
    auto conn = internal::x11::XcbConnection::Create();
#else
    auto conn = internal::stub::StubConnection::Create();
#endif

    if (!conn.ok()) return conn.status();

    return Actions(std::move(conn.value()));
}

Actions::Actions(std::unique_ptr<internal::Connection> conn) noexcept
    : conn(std::move(conn)) {}

Actions::Actions(Actions&& other) noexcept : conn(std::move(other.conn)) {}

Actions& Actions::operator=(Actions&& other) noexcept {
    if (this != &other) {
        conn = std::move(other.conn);
    }

    return *this;
}

std::future<absl::Status> Actions::Perform(
    const Action& action, const action::Target& target) noexcept {
    if (absl::holds_alternative<action::Keystroke>(action)) {
        return conn->Keystroke(absl::get<action::Keystroke>(action), target);
    } else if (absl::holds_alternative<action::KeysPress>(action)) {
        return conn->KeysPress(absl::get<action::KeysPress>(action), target);
    } else if (absl::holds_alternative<action::KeysRelease>(action)) {
        return conn->KeysRelease(absl::get<action::KeysRelease>(action),
                                 target);
    } else if (absl::holds_alternative<action::CursorMove>(action)) {
        return conn->MoveCursor(absl::get<action::CursorMove>(action), target);
    } else if (absl::holds_alternative<action::MousePress>(action)) {
        return conn->MousePress(absl::get<action::MousePress>(action), target);
    } else if (absl::holds_alternative<action::MouseRelease>(action)) {
        return conn->MouseRelease(absl::get<action::MouseRelease>(action),
                                  target);
    } else if (absl::holds_alternative<action::MouseClick>(action)) {
        return conn->MouseClick(absl::get<action::MouseClick>(action), target);
    } else if (absl::holds_alternative<action::NoOp>(action)) {
        return internal::util::Resolve(absl::OkStatus());
    }

    // Should be unreachable, but you can never be too careful
    return internal::util::Resolve(
        absl::UnimplementedError("Not Implemented."));
}

}  // namespace actions
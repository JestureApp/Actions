#include "actions/actions.h"

#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/internal/connection.h"
#include "actions/internal/util.h"

#if defined(__linux)
#include "actions/internal/linux/xcb_connection.h"
#else
#include "actions/internal/stub/stub_connection.h"
#endif

namespace actions {

absl::StatusOr<Actions> Actions::Create(
    std::unique_ptr<internal::Connection> conn) noexcept {
    return Actions(std::move(conn));
}

absl::StatusOr<Actions> Actions::Create() noexcept {
#if defined(__linux)
    auto conn = internal::linux::XcbConnection::Create();
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
        return conn->SendKeystroke(absl::get<action::Keystroke>(action),
                                   target);
    }

    return internal::util::Resolve(
        absl::UnimplementedError("Not Implemented."));
}

}  // namespace actions
#include "actions/actions.h"

#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/internal/connection.h"
#include "actions/internal/util.h"

namespace actions {

absl::StatusOr<Actions> Actions::Create(
    std::unique_ptr<internal::Connection> conn) noexcept {
    return Actions(std::move(conn));
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
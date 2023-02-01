#ifndef ACTIONS_H
#define ACTIONS_H

#include <future>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/action.h"
#include "actions/internal/connection.h"

namespace actions {
/// @brief The dispatcher for actions and the main entry point to the actions
/// API. Encapsulates a connection to the display server.
class Actions {
   private:
    std::unique_ptr<internal::Connection> conn;

   protected:
    Actions(std::unique_ptr<internal::Connection> conn) noexcept;

   public:
    static absl::StatusOr<Actions> Create(
        std::unique_ptr<internal::Connection> conn) noexcept;


    Actions(Actions&) = delete;
    Actions& operator=(Actions&) = delete;

    Actions(Actions&&) noexcept;
    Actions& operator=(Actions&&) noexcept;

    /// @brief Performs the specified `action` on the `target`.
    /// @param action The action to perform.
    /// @param target The target to perform the action on.
    /// @return A future which resolves to `absl::OkStatus()` when the action is
    /// completed successfully or an error status in the case of an error.
    std::future<absl::Status> Perform(const Action& action,
                                      const action::Target& target) noexcept;
};
}  // namespace actions

#endif  // ACTIONS_H
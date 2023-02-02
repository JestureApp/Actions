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

    std::future<absl::Status> SendKeystroke(
        const action::Keystroke& keystroke,
        const action::Target& target) noexcept override;
};
}  // namespace actions::internal::stub

#endif  // ACTIONS_INTERNAL_STUB_STUB_CONNECTION_H
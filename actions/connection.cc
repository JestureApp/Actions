#include "actions/connection.h"

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#if defined(__test__)
#elif defined(__linux__)
#include "actions/linux/xcb_connection.h"
#endif

namespace actions {

absl::StatusOr<std::unique_ptr<Connection>> Connection::Create() noexcept {
#if defined(__test__)
    return absl::UnimplementedError(
        "Connection::Create not implemented for test enviornment");
#elif defined(__linux__)
    auto conn = XcbConnection::Open();

    if (!conn.ok()) return conn.status();

    return conn;
#else
    return absl::UnimplementedError(
        "Connection::Create not implemented for your platform yet");
#endif
}

}  // namespace actions
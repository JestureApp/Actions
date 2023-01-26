#include "actions/linux/dispatcher.h"

#include <absl/status/internal/statusor_internal.h>

#include <future>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/dispatcher_base.h"
#include "actions/keystroke.h"
#include "actions/linux/xcb_connection.h"

namespace actions {
LinuxDispatcher::LinuxDispatcher(std::unique_ptr<XcbConnection> conn) noexcept
    : conn(std::move(conn)) {}

LinuxDispatcher::LinuxDispatcher(LinuxDispatcher&& other) noexcept
    : conn(std::move(other.conn)) {}

LinuxDispatcher& LinuxDispatcher::operator=(LinuxDispatcher&& other) noexcept {
    conn = std::move(other.conn);

    return *this;
}

absl::StatusOr<LinuxDispatcher> LinuxDispatcher::Create() noexcept {
    auto conn = XcbConnection::Open();

    if (!conn.ok()) return conn.status();

    return LinuxDispatcher(
        std::make_unique<XcbConnection>(std::move(conn).value()));
}

std::future<absl::Status> LinuxDispatcher::SendKeystrokes(
    Keystrokes&& keystrokes) {
    std::promise<absl::Status> prom;
    prom.set_value(absl::UnimplementedError("Action not implemented."));

    // CHECKME: will the promises deconstruction cause problems?
    return prom.get_future();
}
}  // namespace actions
#include "actions/internal/util.h"

#include <future>

#include "absl/status/status.h"

namespace actions::internal::util {
std::future<absl::Status> AllOk(
    std::vector<std::future<absl::Status>>&& futures) noexcept {
    return std::async(
        std::launch::deferred,
        [=](std::vector<std::future<absl::Status>> futures) {
            absl::Status status = absl::OkStatus();

            for (auto& fut : futures) {
                status.Update(fut.get());

                if (!status.ok()) return status;
            }

            return absl::OkStatus();
        },
        std::move(futures));
}
}  // namespace actions::internal::util
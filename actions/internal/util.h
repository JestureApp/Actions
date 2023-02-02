#ifndef ACTIONS_INTERNAL_UTIL_H
#define ACTIONS_INTERNAL_UTIL_H

#include <future>
#include <type_traits>

#include "absl/status/status.h"

namespace actions::internal::util {

template <typename Res>
std::future<Res> Resolve(Res&& res) noexcept {
    static_assert(std::is_move_assignable<Res>::value,
                  "`Res` must be move assignable.");

    return std::async(std::launch::deferred,
                      [res = std::move(res)]() { return res; });
}

std::future<absl::Status> AllOk(
    std::vector<std::future<absl::Status>>&& futures) noexcept;

}  // namespace actions::internal::util

#endif  // ACTIONS_INTERNAL_UTIL_H
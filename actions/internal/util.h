#ifndef ACTIONS_INTERNAL_UTIL_H
#define ACTIONS_INTERNAL_UTIL_H

#include <future>
#include <type_traits>

namespace actions::internal::util {

template <typename Res>
std::future<Res> Resolve(Res&& res) noexcept {
    static_assert(std::is_move_assignable<Res>::value,
                  "`Res` must be move assignable.");

    return std::async(std::launch::deferred,
                      [res = std::move(res)]() { return res; });
}

}  // namespace actions::internal::util

#endif  // ACTIONS_INTERNAL_UTIL_H
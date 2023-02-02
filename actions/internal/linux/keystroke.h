#ifndef ACTIONS_INTERNAL_LINUX_KEYSTROKE_H
#define ACTIONS_INTERNAL_LINUX_KEYSTROKE_H

#include <xcb/xcb.h>

#include <unordered_set>

#include "absl/status/statusor.h"

namespace actions::internal::linux {

using Key = xcb_keysym_t;

absl::StatusOr<std::unordered_set<Key>> ParseKeystroke(std::string) noexcept;

}  // namespace actions::internal::linux

#endif  // ACTIONS_INTERNAL_LINUX_KEYSTROKE_H
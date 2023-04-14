#ifndef ACTIONS_INTERNAL_X11_KEYSTROKE_H
#define ACTIONS_INTERNAL_X11_KEYSTROKE_H

#include <xcb/xcb.h>

#include <unordered_set>
#include <vector>

#include "absl/status/statusor.h"

namespace actions::internal::x11 {

using Key = xcb_keysym_t;

absl::StatusOr<std::vector<Key>> ParseKeystroke(std::string) noexcept;

}  // namespace actions::internal::x11

#endif  // ACTIONS_INTERNAL_X11_KEYSTROKE_H
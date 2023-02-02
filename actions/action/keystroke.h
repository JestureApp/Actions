#ifndef ACTIONS_ACTION_KEYSTROKE_H
#define ACTIONS_ACTION_KEYSTROKE_H

#include <unordered_set>
#include <vector>

#if defined(__linux__)
#include "actions/internal/linux/keystroke.h"
#endif

namespace actions::action {

#if defined(__linux__)
using internal::linux::Key;
using internal::linux::ParseKeystroke;
#else
using Key = unsigned int;
absl::StatusOr<std::unordered_set<Key> > ParseKeystroke(std::string) noexcept {
    return std::unordered_set();
}
#endif

/// @brief Represents a keystroke. A collection of keys with associated
/// modifiers.
using Keystroke = std::vector<Key>;

}  // namespace actions::action

#endif  // ACTIONS_ACTION_KEYSTROKE_H
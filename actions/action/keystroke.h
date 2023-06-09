#ifndef ACTIONS_ACTION_KEYSTROKE_H
#define ACTIONS_ACTION_KEYSTROKE_H

#include <unordered_set>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#if defined(__x11__)
#include "actions/internal/x11/keystroke.h"
#endif

namespace actions::action {

#if defined(__x11__)
using internal::x11::Key;
#else
using Key = unsigned int;
#endif

/// @brief Parses a string representing a keystroke. Must be of the form
/// "KEY1 + KEY2 + ..."
///
/// @return A status or a keysequence. In the case of a failure an error status
/// is returned.
absl::StatusOr<std::vector<Key> > ParseKeystroke(std::string) noexcept;

/// @brief Represents a keystroke. A collection of keys with associated
/// modifiers.
using KeySequence = std::vector<Key>;

typedef struct Keystroke {
    KeySequence sequence;
} Keystroke;

typedef struct KeysPress {
    KeySequence sequence;
} KeysPress;

typedef struct KeysRelease {
    KeySequence sequence;
} KeysRelease;

}  // namespace actions::action

#endif  // ACTIONS_ACTION_KEYSTROKE_H
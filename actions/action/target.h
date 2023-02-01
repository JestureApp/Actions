#ifndef ACTIONS_ACTION_TARGET_H
#define ACTIONS_ACTION_TARGET_H

#include "absl/types/variant.h"

namespace actions::action {

namespace target {
/// @brief Indicates that the target of an action is the focused window.
typedef struct {
} Focused;
}  // namespace target

/// @brief The target of an action
using Target = absl::variant<target::Focused>;

}  // namespace actions::action

#endif  // ACTIONS_ACTION_TARGET_H
#ifndef ACTIONS_ACTION_H
#define ACTIONS_ACTION_H

#include "absl/types/variant.h"
#include "actions/action/keystroke.h"
#include "actions/action/mouse.h"
#include "actions/action/target.h"

namespace actions {

namespace action {

/// @brief An action which does nothing.
typedef struct NoOp {
} NoOp;
}  // namespace action

/// @brief The type of an action.
using Action =
    absl::variant<action::Keystroke, action::KeysPress, action::KeysRelease,
                  action::CursorMove, action::MouseClick, action::MousePress,
                  action::MouseRelease, action::NoOp>;

}  // namespace actions

#endif  // ACTIONS_ACTION_H
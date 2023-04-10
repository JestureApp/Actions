#ifndef ACTIONS_ACTION_H
#define ACTIONS_ACTION_H

#include "absl/types/variant.h"
#include "actions/action/cursor_move.h"
#include "actions/action/keystroke.h"
#include "actions/action/target.h"

namespace actions {

namespace action {

typedef struct NoOp {
} NoOp;
}  // namespace action

using Action =
    absl::variant<action::Keystroke, action::CursorMove, action::NoOp>;

}  // namespace actions

#endif  // ACTIONS_ACTION_H
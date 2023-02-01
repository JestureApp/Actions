#ifndef ACTIONS_ACTION_H
#define ACTIONS_ACTION_H

#include "absl/types/variant.h"
#include "actions/action/keystroke.h"
#include "actions/action/target.h"

namespace actions {

using Action = absl::variant<action::Keystroke>;

}

#endif  // ACTIONS_ACTION_H
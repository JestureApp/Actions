#ifndef ACTIONS_ACTION_H
#define ACTIONS_ACTION_H

#include "actions/action/keystroke.h"
#include "absl/types/variant.h"

namespace actions {

    using Action = absl::variant<action::Keystroke>;
    
}

#endif // ACTIONS_ACTION_H
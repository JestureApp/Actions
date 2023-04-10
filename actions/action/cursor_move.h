#ifndef ACTIONS_ACTION_CURSOR_MOVE_H
#define ACTIONS_ACTION_CURSOR_MOVE_H

namespace actions::action {

typedef struct CursorMove {
    double x;
    double y;
    bool relative = true;
} CursorMove;

}  // namespace actions::action

#endif  // ACTIONS_ACTION_CURSOR_MOVE_H
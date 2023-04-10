#ifndef ACTIONS_ACTION_MOUSE_CLICK_H
#define ACTIONS_ACTION_MOUSE_CLICK_H

namespace actions::action {

typedef struct CursorMove {
    double x;
    double y;
    bool relative = true;
} CursorMove;

typedef enum MouseClick { LeftClick, RightClick, MiddleClick } MouseClick;

typedef enum MousePress { LeftPress, RightPress, MiddlePress } MousePress;

typedef enum MouseRelease {
    LeftRelease,
    RightRelease,
    MiddleRelease
} MouseRelease;

}  // namespace actions::action

#endif  // ACTIONS_ACTION_MOUSE_CLICK_H
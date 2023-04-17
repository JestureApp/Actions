#ifndef ACTIONS_ACTION_MOUSE_CLICK_H
#define ACTIONS_ACTION_MOUSE_CLICK_H

namespace actions::action {

/// @brief A action representing the movement of a cursor. If `relative` is
/// true, then movement is relative to the current cursor position.
typedef struct CursorMove {
    double x = 0;
    double y = 0;
    bool relative = true;
} CursorMove;

/// @brief An action representing a mouse click.
typedef enum MouseClick { LeftClick, RightClick, MiddleClick } MouseClick;

/// @brief An action representing a mouse press (no release of the mouse
/// button).
typedef enum MousePress { LeftPress, RightPress, MiddlePress } MousePress;

/// @brief An action representing a mouse release (no press of the mouse
/// button).
typedef enum MouseRelease {
    LeftRelease,
    RightRelease,
    MiddleRelease
} MouseRelease;

}  // namespace actions::action

#endif  // ACTIONS_ACTION_MOUSE_CLICK_H
#ifndef __H_KEYSTROKE__
#define __H_KEYSTROKE__

#include <vector>
namespace actions {

typedef struct {
    char key;
} Keystroke;

typedef std::vector<Keystroke> Keystrokes;

}  // namespace actions

#endif  // __H_KEYSTROKE__
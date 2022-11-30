#ifndef __H_KEYSTROKE__
#define __H_KEYSTROKE__

#include <vector>

#include "absl/status/statusor.h"

namespace actions {
struct Keystroke {
    char key;
    int modifiers;
};

using Keystrokes = std::vector<Keystroke>;

absl::StatusOr<Keystrokes> ParseKeystrokes(const char* keystrokes);
}  // namespace actions

#endif  // __H_KEYSTROKE__
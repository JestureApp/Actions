#include "actions/keystroke.h"

#include "absl/status/statusor.h"

namespace actions {
absl::StatusOr<Keystrokes> ParseKeystrokes(const char* keystrokes) {
  return absl::OkStatus();
}
}  // namespace actions

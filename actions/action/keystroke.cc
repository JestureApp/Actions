#include "actions/action/keystroke.h"

namespace actions::action {
absl::StatusOr<std::vector<Key> > ParseKeystroke(std::string str) noexcept {
#if defined(__linux__)
    return internal::linux::ParseKeystroke(str);
#else
    return std::vector<Key>();
#endif
}
}  // namespace actions::action
#include "actions/action/keystroke.h"

namespace actions::action {
absl::StatusOr<std::vector<Key> > ParseKeystroke(std::string str) noexcept {
#if defined(__x11__)
    return internal::x11::ParseKeystroke(str);
#else
    return std::vector<Key>();
#endif
}
}  // namespace actions::action
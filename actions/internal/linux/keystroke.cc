#include "actions/internal/linux/keystroke.h"

#include <X11/Xlib.h>

#include <map>
#include <sstream>
#include <string>

namespace actions::internal::linux {
const static std::map<std::string, std::string> symbol_map{
    {"alt", "alt_L"},
    {"ctrl", "control_L"},
    {"control", "control_L"},
    {"meta", "meta_L"},
    {"super", "super_L"},
    {"shift", "shift_L"},
    {"enter", "return"},
    {
        "return",
        "Return",
    }};

absl::StatusOr<std::unordered_set<Key>> ParseKeystroke(
    std::string&& str) noexcept {
    std::stringstream ss(std::move(str));
    std::string s;
    std::unordered_set<Key> keys;

    while (std::getline(ss, str, '+')) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        auto it = symbol_map.find(str);

        if (it != symbol_map.end()) str = it->second;

        KeySym sym = XStringToKeysym(str.c_str());

        if (sym == NoSymbol) {
            return absl::InvalidArgumentError("Unrecognized key: " + str);
        }
    }

    return keys;
}
}  // namespace actions::internal::linux
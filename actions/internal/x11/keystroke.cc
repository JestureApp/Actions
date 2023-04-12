#include "actions/internal/x11/keystroke.h"

#include <X11/Xlib.h>

#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace actions::internal::x11 {
const static std::map<std::string, std::string> symbol_map{
    {"alt", "Alt_L"},
    {"ctrl", "Control_L"},
    {"control", "Control_L"},
    {"meta", "Meta_L"},
    {"super", "Super_L"},
    {"shift", "Shift_L"},
    {"enter", "Return"},
    {
        "return",
        "Return",
    },
    {"pgup", "Page_Up"},
    {"pgdown", "Page_Down"}};

absl::StatusOr<std::vector<Key>> ParseKeystroke(std::string str) noexcept {
    std::stringstream ss(std::move(str));
    std::string s;
    std::vector<Key> keys;

    while (std::getline(ss, str, ',')) {
        std::stringstream ss2(std::move(str));
        while (std::getline(ss2, str, '+')) {
            std::string lookup_str = str;
            std::transform(lookup_str.begin(), lookup_str.end(),
                           lookup_str.begin(), ::tolower);

            auto it = symbol_map.find(lookup_str);

            if (it != symbol_map.end()) str = it->second;

            KeySym sym = XStringToKeysym(str.c_str());

            if (sym == NoSymbol) {
                return absl::InvalidArgumentError("Unrecognized key: " + str);
            }

            keys.push_back(sym);
        }
    }

    return keys;
}
}  // namespace actions::internal::x11
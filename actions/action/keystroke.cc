#include "actions/action/keystroke.h"

namespace actions::action {
std::unordered_set<KeyModifier> operator|(KeyModifier mod1, KeyModifier mod2) noexcept {
    return std::unordered_set<KeyModifier>{mod1, mod2};
}

std::unordered_set<KeyModifier> operator|(std::unordered_set<KeyModifier>&& mods, KeyModifier mod) noexcept {
    mods.insert(mod);

    return mods;
}

std::unordered_set<KeyModifier> operator|(KeyModifier mod, std::unordered_set<KeyModifier>&& mods) noexcept {
    return std::move(mods) | mod;
}

}
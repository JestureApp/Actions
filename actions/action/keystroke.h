#ifndef ACTIONS_ACTION_KEYSTROKE_H
#define ACTIONS_ACTION_KEYSTROKE_H

#include <unordered_set>
#include <vector>

namespace actions::action {

/// @brief Represents various modifier keys that modify the meaning of a keystroke.
enum class KeyModifier {
    Ctrl,
    Alt,
    Shift,
    Meta,
};

std::unordered_set<KeyModifier> operator|(KeyModifier mod1, KeyModifier mod2) noexcept;
std::unordered_set<KeyModifier> operator|(std::unordered_set<KeyModifier>&& mods, KeyModifier mod) noexcept;
std::unordered_set<KeyModifier> operator|(KeyModifier mod, std::unordered_set<KeyModifier>&& mods) noexcept;


/// @brief Represents a keystroke. A collection of keys with associated modifiers.
typedef struct {
    /// @brief The modifiers that are active for the keystroke.
    std::unordered_set<KeyModifier> modifiers;

    /// @brief The keys in the keystroke
    std::vector<char> keys;
} Keystroke;



}

#endif // ACTIONS_ACTION_KEYSTROKE_H
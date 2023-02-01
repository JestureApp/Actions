#include "gtest/gtest.h"

#include "actions/action/keystroke.h"

using namespace actions::action;

TEST(KeyModifierTests, BitOr2Mods) {
    auto mods = KeyModifier::Ctrl | KeyModifier::Alt;

    EXPECT_TRUE(mods.find(KeyModifier::Ctrl) != mods.end());
    EXPECT_TRUE(mods.find(KeyModifier::Alt) != mods.end());
}

TEST(KeyModifierTest, BitOr3Mods) {
    auto mods = KeyModifier::Ctrl | KeyModifier::Shift | KeyModifier::Alt;

    EXPECT_TRUE(mods.find(KeyModifier::Ctrl) != mods.end());
    EXPECT_TRUE(mods.find(KeyModifier::Alt) != mods.end());
    EXPECT_TRUE(mods.find(KeyModifier::Shift) != mods.end());
}

TEST(KeyModifierTest, BitOrIdempotent) {
    auto mods = KeyModifier::Ctrl | KeyModifier::Ctrl;

    EXPECT_EQ(1, mods.size());
}
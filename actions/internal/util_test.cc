#include "actions/internal/util.h"

#include "gtest/gtest.h"

using namespace actions::internal::util;

TEST(ResolveTests, ResolveReturnsRes) {
    auto res = Resolve<int>(4);

    EXPECT_EQ(4, res.get());
}

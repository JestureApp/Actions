#include "actions/linux/dispatcher.h"

#include <gtest/gtest.h>

#include <memory>

#include "absl/status/status.h"

using Dispatcher = actions::LinuxDispatcher;

// class LinuxDispatcherTest : public ::testing::Test {
//    protected:
//     void SetUp() override { dispatcher = Dispatcher::Create(); }

//     absl::StatusOr<std::unique_ptr<Dispatcher>> dispatcher;
// };

// TEST_F(LinuxDispatcherTest, CreateReturnsUnimplemented) {
//     ASSERT_FALSE(dispatcher.ok());
//     ASSERT_EQ(dispatcher.status().code(), absl::StatusCode::kUnimplemented);
// }
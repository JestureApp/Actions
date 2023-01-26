#include "actions/linux/dispatcher.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "absl/status/status.h"
#include "actions/linux/xcb_connection.h"
#include "gmock/gmock.h"

using Dispatcher = actions::LinuxDispatcher;

class MockConnection : public actions::XcbConnection {
   public:
    MockConnection() : actions::XcbConnection(nullptr) {}

    // MOCK_METHOD(void, Foo, (), (override));
};

// TEST(LinuxDispatcherTest, CallsFoo) {
//     auto mock = std::make_unique<MockConnection>();

//     EXPECT_CALL(*mock, Foo()).Times(1);

//     Dispatcher dispatcher(std::move(mock));

//     actions::Keystrokes keystrokes;

//     dispatcher.SendKeystrokes(std::move(keystrokes));
// }
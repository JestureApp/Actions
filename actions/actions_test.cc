#include "actions/actions.h"

#include <future>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/internal/connection.h"
#include "actions/internal/util.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::_;
using testing::ByMove;
using testing::Return;

using namespace actions;
using namespace actions::internal;

class MockConnection : public Connection {
   public:
    MOCK_METHOD(std::future<absl::Status>, SendKeystroke,
                (const action::Keystroke&, const action::Target& target),
                (noexcept, override));
};

TEST(ActionsTest, PerformKeystrokeCallsSendKeystroke) {
    auto conn = std::make_unique<MockConnection>();
    std::future<absl::Status> fut = util::Resolve(absl::OkStatus());

    EXPECT_CALL(*conn, SendKeystroke(_, _))
        .WillOnce(Return(ByMove(std::move(fut))));

    auto actions = Actions::Create(std::move(conn));

    EXPECT_TRUE(actions.ok());

    EXPECT_EQ(
        absl::OkStatus(),
        actions->Perform(action::Keystroke{}, action::target::Focused{}).get());
}
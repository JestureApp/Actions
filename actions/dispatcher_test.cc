#include "actions/dispatcher.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <map>

#include "absl/status/status.h"
#include "actions/connection.h"
#include "actions/keystroke.h"
#include "actions/promise.h"

using namespace actions;
using ::testing::_;
using ::testing::ByMove;
using ::testing::Return;

class MockPromise : public Promise<absl::Status> {
   public:
    static std::unique_ptr<MockPromise> Make(int till_true,
                                             absl::Status status) {
        return std::make_unique<MockPromise>(next_id++, till_true, status);
    }

    static int GetNCall(int id) {
        std::unique_lock<std::mutex> lk(mutex);

        return poll_calls[id];
    }

    MockPromise(int id, int till_true, absl::Status status)
        : id(id), till_true(till_true), status(status) {
        std::unique_lock<std::mutex> lk(mutex);

        poll_calls[id] = 0;
    }

    MockPromise(MockPromise&& other) noexcept {
        id = other.id;
        other.id = 0;

        till_true = other.till_true;
        other.till_true = 0;

        status = std::move(other.status);
    }

    int GetId() noexcept { return id; }

    bool Poll() noexcept override {
        {
            std::unique_lock<std::mutex> lk(mutex);
            poll_calls[id] += 1;
        }

        if (!till_true) {
            set_value(status);
            return true;
        }

        till_true -= 1;
        return false;
    }

   private:
    static inline std::map<int, int> poll_calls;
    static inline std::mutex mutex;
    static inline int next_id = 0;

    int id;
    int till_true;
    absl::Status status;
};

class MockConnection : public Connection {
   public:
    MOCK_METHOD(std::unique_ptr<Promise<absl::Status>>, SendKeystroke,
                (Keystroke & keystroke), (noexcept, override));
};

TEST(TestDispatcher, CallsPollUntilReturnsTrue) {
    auto prom = MockPromise::Make(2, absl::OkStatus());
    int prom_id = prom->GetId();

    auto conn = std::make_unique<MockConnection>();
    EXPECT_CALL(*conn, SendKeystroke(_))
        .WillOnce(Return(ByMove(std::move(prom))));

    auto dispatcher = Dispatcher::Create(std::move(conn));

    EXPECT_TRUE(dispatcher.ok());

    Keystroke keystroke;

    dispatcher->SendKeystroke(keystroke).get().IgnoreError();

    EXPECT_EQ(3, MockPromise::GetNCall(prom_id));
}

TEST(TestDispatcher, CanChainAwaits) {
    auto prom1 = MockPromise::Make(2, absl::OkStatus());
    int prom1_id = prom1->GetId();

    auto prom2 = MockPromise::Make(0, absl::OkStatus());
    int prom2_id = prom2->GetId();

    auto conn = std::make_unique<MockConnection>();
    EXPECT_CALL(*conn, SendKeystroke(_))
        .WillOnce(Return(ByMove(std::move(prom1))))
        .WillOnce(Return(ByMove(std::move(prom2))));

    auto dispatcher = Dispatcher::Create(std::move(conn));

    EXPECT_TRUE(dispatcher.ok());

    Keystroke keystroke;

    dispatcher->SendKeystroke(keystroke).get().IgnoreError();

    EXPECT_EQ(3, MockPromise::GetNCall(prom1_id));

    dispatcher->SendKeystroke(keystroke).get().IgnoreError();

    EXPECT_EQ(1, MockPromise::GetNCall(prom2_id));
}

TEST(TestDispatcher, FutureResolutionReturnsCorrectStatus) {
    auto prom1 = MockPromise::Make(0, absl::OkStatus());

    auto prom2 = MockPromise::Make(0, absl::UnknownError("foo"));

    auto conn = std::make_unique<MockConnection>();
    EXPECT_CALL(*conn, SendKeystroke(_))
        .WillOnce(Return(ByMove(std::move(prom1))))
        .WillOnce(Return(ByMove(std::move(prom2))));

    auto dispatcher = Dispatcher::Create(std::move(conn));

    EXPECT_TRUE(dispatcher.ok());

    Keystroke keystroke;

    EXPECT_EQ(dispatcher->SendKeystroke(keystroke).get(), absl::OkStatus());

    EXPECT_EQ(dispatcher->SendKeystroke(keystroke).get(),
              absl::UnknownError("foo"));
}

// TEST(TestDispatcher, DispatcherStill)
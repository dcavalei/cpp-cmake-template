#include "lib/di/FooBar/fooBar.h"

#include <gtest/gtest.h>
#include "mocks/FooMock.h"
#include "mocks/BarMock.h"

#include <memory>

class FooBarTest : public ::testing::Test {
  protected:
    void SetUp() override {
        fooMock = std::make_shared<FooMock>();
        barMock = std::make_shared<BarMock>();

        target = std::make_shared<lib::di::FooBar>(fooMock, barMock);
    }

    std::shared_ptr<FooMock> fooMock;
    std::shared_ptr<BarMock> barMock;
    std::shared_ptr<lib::di::FooBar> target;
};

TEST_F(FooBarTest, fooBar) {
    EXPECT_CALL(*fooMock, foo());
    EXPECT_CALL(*barMock, bar());

    target->fooBar();
}

#pragma once

#include <gmock/gmock.h>

#include "lib/di/Foo/fooInterface.h"

using namespace lib::di;

class FooMock : public FooInterface {
  public:
    FooMock() = default;
    ~FooMock() override = default;

    MOCK_METHOD(void, foo, (), (override));
};

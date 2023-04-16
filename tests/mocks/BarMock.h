#pragma once

#include <gmock/gmock.h>

#include "lib/di/Bar/barInterface.h"

using namespace lib::di;

class BarMock : public BarInterface {
  public:
    BarMock() = default;
    ~BarMock() override = default;

    MOCK_METHOD(void, bar, (), (override));
};

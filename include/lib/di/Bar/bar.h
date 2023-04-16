#pragma once

#include "barInterface.h"

namespace lib::di {
  class Bar : public BarInterface {
    public:
      void bar() override;
  };
}

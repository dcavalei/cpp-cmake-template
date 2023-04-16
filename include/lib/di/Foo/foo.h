#pragma once

#include "fooInterface.h"

namespace lib::di {
  class Foo : public FooInterface {
    public:
      void foo() override;
  };
}

#pragma once

namespace lib::di {
  class FooInterface {
    public:
      virtual ~FooInterface() = default;

      virtual void foo() = 0;
  };
}

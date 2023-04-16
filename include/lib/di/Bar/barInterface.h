#pragma once

namespace lib::di {
  class BarInterface {
    public:
      virtual ~BarInterface() = default;

      virtual void bar() = 0;
  };
}

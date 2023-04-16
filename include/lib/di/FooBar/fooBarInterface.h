#pragma once

namespace lib::di {
  class FooBarInterface {
    public:
      virtual ~FooBarInterface() = default;

      virtual void fooBar() = 0;
  };
}

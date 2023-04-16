#pragma once

#include "fooBarInterface.h"
#include "lib/di/Foo/fooInterface.h"
#include "lib/di/Bar/barInterface.h"

#include <memory>

namespace lib::di {
  class FooBar : public FooBarInterface {
    public:
      FooBar(std::shared_ptr<FooInterface> foo, std::shared_ptr<BarInterface> bar);

      void fooBar() override;

    private:
      std::shared_ptr<FooInterface> foo;
      std::shared_ptr<BarInterface> bar;
  };
}

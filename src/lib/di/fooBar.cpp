#include <utility>

#include "lib/di/FooBar/fooBar.h"

namespace lib::di {
  FooBar::FooBar(std::shared_ptr<FooInterface> foo,
                 std::shared_ptr<BarInterface> bar)
          : foo(std::move(foo)),
            bar(std::move(bar)) {}

  void FooBar::fooBar() {
      foo->foo();
      bar->bar();
  };
}

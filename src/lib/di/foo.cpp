#include "lib/di/Foo/foo.h"

#include <iostream>

namespace lib::di {
  void Foo::foo() {
      std::cout << "Foo::foo()" << std::endl;
  };
}

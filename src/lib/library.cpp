#include "lib/library.h"

#include <iostream>
#include "fmt/format.h"

namespace lib {
  void hello() {
      std::cout << "Hello, World!" << std::endl;
  }

  void hello_using_fmt() {
      std::cout << fmt::format("Hello, {}!", "World") << std::endl;
  }
}

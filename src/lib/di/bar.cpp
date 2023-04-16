#include "lib/di/Bar/bar.h"

#include <iostream>

namespace lib::di {
  void Bar::bar() {
      std::cout << "Bar::bar()" << std::endl;
  };
}

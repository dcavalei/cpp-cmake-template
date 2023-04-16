#include <memory>
#include "lib/di/Foo/foo.h"
#include "lib/di/Bar/bar.h"
#include "lib/di/FooBar/fooBar.h"

using namespace lib::di;

int main() {
    // Create a Foo and Bar instance
    std::shared_ptr<FooInterface> foo = std::make_shared<Foo>();
    std::shared_ptr<BarInterface> bar = std::make_shared<Bar>();

    foo->foo();
    bar->bar();

    // Create a FooBar instance, passing in the Foo and Bar pointers
    std::shared_ptr<FooBarInterface> fooBar = std::make_shared<FooBar>(foo, bar);

    fooBar->fooBar();

    return 0;
}

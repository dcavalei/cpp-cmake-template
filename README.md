# Cmake Project

## Modern CMake

Modern CMake is target based. Everything is a target. A target can be an executable, a library, a test, a package, etc.
Certain commands are strongly discouraged since there are new target based commands that do the same thing.
- `include_directories()`, discouraged. Use `target_include_directories()`.
- `add_definitions()`, discouraged. Use `target_compile_definitions()`.
- `link_libraries()`, discouraged. Use `target_link_libraries()`.

You should check the cmake [documentation](https://cmake.org/cmake/help/latest/) for each command that you use, if the command is discouraged, it will be mentioned in the documentation.

---

This README-md will guide you through the process of creating a CMake project.
The project structure presented in this repository is not the same as the one presented in this README.md

---
- Project Structure: `src`, `include`, `tests`, `lib`.
- Root `CMakeLists.txt` will distribute responsibilities and show the available options.
- `tree`:
  ```tree
  .
  ├── CMakeLists.txt
  ├── include
  ├── lib
  │   ├── CMakeLists.txt
  │   └── fmt
  │       └── CMakeLists.txt
  ├── src
  │   ├── bar
  │   │   ├── bar.cpp
  │   │   ├── bar.h
  │   │   └── CMakeLists.txt
  │   ├── CMakeLists.txt
  │   ├── foo
  │   │   ├── CMakeLists.txt
  │   │   ├── foo.cpp
  │   │   └── foo.h
  │   ├── fooBar
  │   │   ├── CMakeLists.txt
  │   │   ├── fooBar.cpp
  │   │   └── fooBar.h
  │   └── main
  │       ├── CMakeLists.txt
  │       └── main.cpp
  └── tests
      ├── CMakeLists.txt
      ├── mocks
      │   ├── barMock.h
      │   └── fooMock.h
      └── unit
          └── fooBar_test.cpp
  ```
---
- `cmake_minimum_required()`, sets the minimum required version of cmake for a project.
- `project()`,
  ```cmake
  cmake_minimum_required(VERSION 3.24)
  project(name)
  
  set(CMAKE_CXX_STANDARD 17)
  ```
---
- `option()`, In CMake 3.13 and above the `option()` command prefers to do nothing when a normal variable of the given name already exists.
- `MATCHES`, works with regex.
  ```cmake
  if (CMAKE_BUILD_TYPE MATCHES ^[Dd]ebug)
    option(BUILD_TESTS "Build tests" ON)
    option(BUILD_DOC "Build documentation" ON)
  else ()
    option(CMAKE_BUILD_TYPE "Build type" Release)
  endif ()
  ```
---
- `PROJECT_IS_TOP_LEVEL`, set by the `project()` command.
- `enable_testing()`, enables testing for this directory and below.
- `add_subdirectory()`, adds a subdirectory to the build, it will look for a `CMakeLists.txt` file in the specified directory. The new `CMakeLists.txt` will be processed before the old one.
- `find_package()`
  ```cmake
  if (PROJECT_IS_TOP_LEVEL AND BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
  endif()
  if (PROJECT_IS_TOP_LEVEL AND BUILD_DOC)
    find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
    doxygen_add_docs(doc COMMENT "Generate documentation" include src)
  endif ()
  ```
---
- Distribute responsibilities with `add_subdirectory()`.
  ```cmake
  # add_subdirectory(tests)
  add_subdirectory(lib)
  add_subdirectory(src)
  add_subdirectory(include)
  ```
---
## lib
- Distribute responsibilities with `add_subdirectory()`.
  ```tree
  lib
  ├── CMakeLists.txt
  └── fmt
      └── CMakeLists.txt
  ```
- `include()`, load and run CMake code from a file or module.
- `FetchContent_Declare()`, allows you to download external libraries.
-  `FetchContent_MakeAvailable()`, ensures that each of the named dependencies are made available to the project by the time it returns.
- `lib/CMakeLists.txt`:
  ```cmake
  include(FetchContent)
  
  add_subdirectory(fmt)
  ```
- `fmt/CMakeLists.txt`:
  ```cmake
  project(fmt)

  FetchContent_Declare(
          ${PROJECT_NAME}
          GIT_REPOSITORY https://github.com/fmtlib/fmt.git
          GIT_TAG 9.1.0
  )
  FetchContent_MakeAvailable(${PROJECT_NAME})
  ```
---
## src
- Distribute responsibilities with `add_subdirectory()`.
- `src/CMakeLists.txt`:
  ```cmake
  add_subdirectory(foo)
  add_subdirectory(bar)
  add_subdirectory(fooBar)
  add_subdirectory(main)
  ```
- Each component (`foo`, `bar` and `fooBar`) is a `STATIC` library.
- - `foo` doesn't have any dependencies.
- - `bar` depends on the `fmt` library.
- - `fooBar` depends on `foo` and `bar`.
- - `main` is `main` :^).
```tree
src
├── bar
│   ├── bar.cpp
│   ├── bar.h
│   └── CMakeLists.txt
├── CMakeLists.txt
├── foo
│   ├── CMakeLists.txt
│   ├── foo.cpp
│   └── foo.h
├── fooBar
│   ├── CMakeLists.txt
│   ├── fooBar.cpp
│   └── fooBar.h
└── main
    ├── CMakeLists.txt
    └── main.cpp
```
---
### foo
- `set()`, create a new variable.
- `add_library()`, create a new target library. The first argument is the library name, the `STATIC` keyword is used to create a static library (which is the default type), after that is library source lists. The `ALIAS` is used to create an alias of our library name. The first argument is the aliased name, the second is the original target name.
- `target_include_directories()`, add a new include directory to our target. The `INTERFACE` sets the [scope](https://stackoverflow.com/questions/26243169/cmake-target-include-directories-meaning-of-scope) of that directory.
- `foo/CMakeLists.txt`:
  ```cmake
  project(foo)
  
  set(SOURCES foo.cpp)
  set(HEADERS foo.h)
  
  add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
  add_library(PRJ::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
  
  target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
  ```
- `foo/foo.h`:
  ```c++
  #pragma once
  
  namespace ns {
    class Foo {
      public:
        virtual ~Foo() = default;
        virtual void foo();
    };
  }
  ```
- `foo/foo.cpp`:
  ```c++
  #include "foo.h"
  
  #include <iostream>
  
  namespace ns {
    void Foo::foo() {
      std::cout << "foo" << std::endl;
    }
  }
  ```
---
### bar
- `bar` uses `fmt::fmt` internally.
- `target_link_libraries()`, link the dependencies of a target. The `PRIVATE` keyword sets de scope.
- `bar/CMakeLists.txt`:
  ```cmake
  project(bar)
    
  set(SOURCES bar.cpp)
  set(HEADERS bar.h)
  
  add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
  add_library(PRJ::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
  
  target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
  ```
- `bar/bar.h`:
  ```c++
  #pragma once
  
  namespace ns {
    class Bar {
      public:
        virtual ~Bar() = default;
        virtual void bar();
    };
  }
  ```
- `bar/bar.cpp`:
  ```c++
  #include "bar.h"
  
  #include <iostream>
  #include "fmt/format.h"
  
  namespace ns {
    void Bar::bar() {
      std::cout << fmt::format("{}", "bar") << std::endl;
    }
  }
  ```
---
### fooBar
- `fooBar` uses both `foo` and `bar` (no need to link `fmt::fmt` since it is used in the private implementation of `bar`, not exposed on the header).
- `fooBar/CMakeLists.txt`:
  ```cmake
  project(fooBar)
    
  set(SOURCES fooBar.cpp)
  set(HEADERS fooBar.h)
  
  add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
  add_library(PRJ::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
  
  target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${PROJECT_NAME} PRIVATE PRJ::foo PRJ::bar)
  ```
- `fooBar/fooBar.h`:
  ```c++
  #pragma once
  
  #include "foo.h"
  #include "bar.h"
  
  #include <memory>
  
  namespace ns {
    class FooBar {
      public:
        FooBar(std::shared_ptr<Foo>, std::shared_ptr<Bar>);
        void fooBar();
      private:
        std::shared_ptr<Foo> _foo;
        std::shared_ptr<Bar> _bar;
    };
  }
  ```
- `fooBar/fooBar.cpp`:
  ```c++
  #include "fooBar.h"
  
  namespace ns {
    FooBar::FooBar(std::shared_ptr<Foo> foo, std::shared_ptr<Bar> bar)
      : _foo(std::move(foo)), _bar(std::move(bar)) {}
  
    void FooBar::fooBar() {
      _foo->foo();
      _bar->bar();
    }
  }
  ```
---
### main
- `main` uses `foo`, `bar` and `fooBar`.
- `add_executable()`, create a new executable target. The first argument is the executable name. After the name we pass the source lists.
- `main/CMakeLists.txt`:
  ```cmake
  project(main)
  
  add_executable(${PROJECT_NAME} main.cpp)
  target_link_libraries(${PROJECT_NAME} PRIVATE PRJ::foo PRJ::bar PRJ::fooBar)
  ```
- `main/main.cpp`:
  ```c++
  #include "foo.h" // not needed
  #include "bar.h" // not needed
  #include "fooBar.h"
  
  int main() {
    auto foo = std::make_shared<ns::Foo>();
    auto bar = std::make_shared<ns::Bar>();
  
    foo->foo();
    bar->bar();
  
    auto fooBar = std::make_shared<ns::FooBar>(foo, bar);
  
    fooBar->fooBar();
  }
  ```
---
## tests
- Building tests for our targets (`foo`, `bar` and `fooBar`).
  ```tree
  tests
  ├── CMakeLists.txt
  ├── mocks
  │   ├── barMock.h
  │   └── fooMock.h
  └── unit
      └── fooBar_test.cpp
  ```
- `foreach()`, iterate over a list of items.
- `get_filename_component()`, get a component of a file name. The `NAME_WE` argument gets the file name without extension.
- `gtest_discover_tests()`, discover tests in a given executable. ctest will run the tests.
- `tests/CMakeLists.txt`:
  ```cmake
  include(FetchContent)
  
  FetchContent_Declare(
          googletest
          GIT_REPOSITORY https://github.com/google/googletest.git
          GIT_TAG release-1.12.1
  )
  FetchContent_MakeAvailable(googletest)
  
  include(GoogleTest)
  
  set(MOCKS_HEADERS mocks/fooMock.h mocks/barMock.h)
  set(TESTS_SOURCES unit/fooBar_test.cpp)
  set(ALL_TARGETS PRJ::foo PRJ::bar PRJ::fooBar)
  
  add_library(${PROJECT_NAME}_mocks STATIC ${MOCKS_HEADERS})
  target_include_directories(${PROJECT_NAME}_mocks PUBLIC mocks)
  target_link_libraries(${PROJECT_NAME}_mocks PUBLIC ${ALL_TARGETS} GTest::gmock_main)
  
  foreach (file IN LISTS TESTS_SOURCES)
      get_filename_component(name ${file} NAME_WE)
      add_executable(${name} ${file})
      target_include_directories(${name} PUBLIC unit)
      target_link_libraries(${name} PRIVATE ${ALL_TARGETS} ${PROJECT_NAME}_mocks GTest::gtest_main)
      gtest_discover_tests(${name})
  endforeach ()
  ```
- `tests/mocks/fooMock.h`:
  ```c++
  #pragma once
  
  #include <gmock/gmock.h>
  
  #include "foo.h"
  
  class FooMock : public ns::Foo {
    public:
      FooMock() = default;
      ~FooMock() override = default;
  
      MOCK_METHOD(void, foo, (), (override));
  };
  ```
- `tests/mocks/barMock.h`:
  ```c++
  #pragma once
  
  #include <gmock/gmock.h>
  
  #include "bar.h"
  
  class BarMock : public ns::Bar {
    public:
      BarMock() = default;
      ~BarMock() override = default;
  
      MOCK_METHOD(void, bar, (), (override));
  };
  ```
- `tests/unit/fooBar_test.cpp`:
  ```c++
  #include "fooBar.h"
  
  #include <gtest/gtest.h>
  #include "fooMock.h"
  #include "barMock.h"
  
  #include <memory>
  
  class FooBarTest : public ::testing::Test {
    protected:
      void SetUp() override {
        fooMock = std::make_shared<FooMock>();
        barMock = std::make_shared<BarMock>();
  
        target = std::make_shared<ns::FooBar>(fooMock, barMock);
      }
  
      std::shared_ptr<FooMock> fooMock{nullptr};
      std::shared_ptr<BarMock> barMock{nullptr};
      std::shared_ptr<ns::FooBar> target{nullptr};
  };
  
  TEST_F(FooBarTest, fooBar) {
    EXPECT_CALL(*fooMock, foo());
    EXPECT_CALL(*barMock, bar());
  
    target->fooBar();
  }
  ```

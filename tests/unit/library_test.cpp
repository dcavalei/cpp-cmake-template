#include "lib/library.h"

#include <gtest/gtest.h>

TEST(LibraryTest, hello) {
    testing::internal::CaptureStdout();

    lib::hello();

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Hello, World!\n");
}

TEST(LibraryTest, hello_using_fmt) {
    testing::internal::CaptureStdout();

    lib::hello_using_fmt();

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Hello, World!\n");
}

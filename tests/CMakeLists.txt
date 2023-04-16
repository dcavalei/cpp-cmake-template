FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TESTS_SOURCES "*_test.cpp")
file(GLOB_RECURSE MOCKS_HEADERS "mocks/*.h")

include(GoogleTest)

add_library(${PROJECT_NAME}_mocks STATIC ${MOCKS_HEADERS})
target_include_directories(${PROJECT_NAME}_mocks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_mocks PUBLIC ${PROJECT_NAME} GTest::gmock_main)

foreach (file IN LISTS TESTS_SOURCES)
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})
    target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${name} PRIVATE ${PROJECT_NAME} ${PROJECT_NAME}_mocks GTest::gtest_main)
    gtest_discover_tests(${name})
endforeach ()

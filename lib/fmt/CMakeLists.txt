project(fmt)

FetchContent_Declare(
        ${PROJECT_NAME}
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(${PROJECT_NAME})

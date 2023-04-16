function(setup_library)

    set(options STATIC SHARED HELP)
    set(oneValueArgs NAME)
    set(multiValueArgs ALIAS DEPENDS)
    cmake_parse_arguments(TARGET "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Usage handling
    if (TARGET_HELP OR NOT TARGET_NAME)
        message(FATAL_ERROR "setup_library(
        NAME <name>
        [DEPENDS <lib_name>...]
        [ALIAS <alias>...]
        [SHARED|STATIC]
        [HELP]
        )")
    endif ()

    # Set static or shared library
    if (TARGET_SHARED AND TARGET_STATIC)
        message(FATAL_ERROR "setup_library: Cannot set both SHARED and STATIC")
    elseif (TARGET_SHARED)
        add_library(${TARGET_NAME} SHARED)
    else ()
        add_library(${TARGET_NAME} STATIC)
    endif ()

    # Set source files
    set(src-pattern "src/*.cpp")
    list(INSERT src-pattern 0 CONFIGURE_DEPENDS)
    file(GLOB_RECURSE src-list ${src-pattern})

    target_sources(${TARGET_NAME} PRIVATE ${src-list})
    target_include_directories(${TARGET_NAME} PUBLIC include)
    target_link_libraries(${TARGET_NAME} PRIVATE ${TARGET_DEPENDS})

    # Set alias
    foreach (arg IN LISTS TARGET_ALIAS)
        add_library(${arg} ALIAS ${TARGET_NAME})
    endforeach ()

endfunction()

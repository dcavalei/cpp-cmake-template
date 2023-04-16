file(GLOB_RECURSE EXAMPLES_SOURCES "main/*.cpp")

foreach (file IN LISTS EXAMPLES_SOURCES)
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})
    target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
endforeach ()

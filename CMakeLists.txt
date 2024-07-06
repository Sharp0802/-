cmake_minimum_required(VERSION 3.27)
project(tron)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(useClang)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else ()
    add_compile_options(-stdlib=libc++)
    link_libraries(c++ c++abi)
endif ()

add_subdirectory(cmake/stb)
add_subdirectory(sub/glm)
add_subdirectory(sub/soil)
add_subdirectory(tron)
cmake_minimum_required(VERSION 3.27)
project(tron)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(useClang)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-stdlib=libc++>)

set(GLFW_LIBRARY_TYPE STATIC)
set(SOIL_LIBRARY_TYPE STATIC)

add_subdirectory(cmake/glew)
add_subdirectory(cmake/stb)
add_subdirectory(sub/glfw)
add_subdirectory(sub/glm)
add_subdirectory(sub/soil)
add_subdirectory(tron)
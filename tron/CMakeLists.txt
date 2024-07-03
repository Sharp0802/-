project(tron)

find_package(OpenGL REQUIRED)
find_package(GLEW   REQUIRED)
find_package(glfw3  REQUIRED)

file(GLOB SOURCES src/*.cxx)
file(GLOB HEADERS *.h)

add_compile_options(-stdlib=libc++ -fmacro-prefix-map=${CMAKE_CURRENT_LIST_DIR}=.)
add_executable(tron ${SOURCES} ${HEADERS})
set_target_properties(tron PROPERTIES
    CXX_STANDARD 26
)
target_include_directories(tron PRIVATE .)
target_precompile_headers(tron PRIVATE pch.h)
target_link_libraries(tron PRIVATE
        # SUBMODULES
        glm::glm
        stb
        # PACKAGES
        OpenGL::GL
        OpenGL::GLU
        OpenGL::OpenGL
        GLEW::GLEW
        glfw
        #
        c++
        c++abi
)

add_custom_command(TARGET tron POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "${CMAKE_CURRENT_BINARY_DIR}/assets"
)

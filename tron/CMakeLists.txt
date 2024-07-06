project(tron)

find_package(OpenGL REQUIRED)

file(GLOB SOURCES src/*.cxx)
file(GLOB HEADERS *.h)

add_executable(tron ${SOURCES} ${HEADERS})
set_target_properties(tron PROPERTIES
    CXX_STANDARD 26
)
target_compile_options(tron PRIVATE -fmacro-prefix-map=${CMAKE_CURRENT_LIST_DIR}=.)

target_include_directories(tron PRIVATE .)
target_precompile_headers(tron PRIVATE pch.h)
target_link_libraries(tron PRIVATE
        # SUBMODULES
        glm::glm
        stb
        soil
        # PACKAGES
        OpenGL::GL
        GLEW::GLEW
        glfw
)

add_custom_command(TARGET tron POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "${CMAKE_CURRENT_BINARY_DIR}/assets"
)

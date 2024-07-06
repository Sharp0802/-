project(glew)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(GLEW_VERSION 2.2.0)

    file(
            DOWNLOAD "https://github.com/nigels-com/glew/releases/download/glew-${GLEW_VERSION}/glew-${GLEW_VERSION}-win32.zip"
            "${CMAKE_CURRENT_BINARY_DIR}/glew.zip"
    )
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf glew.zip
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )

    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
        set(GLEW_PLATFORM "Win32")
    elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
        set(GLEW_PLATFORM "x64")
    else ()
        message(FATAL_ERROR "non-x86 Windows is not supported")
    endif ()

    set(GLEW_INCLUDES_PATH "${CMAKE_CURRENT_BINARY_DIR}/glew-${GLEW_VERSION}/include")
    set(GLEW_BIN_PATH "${CMAKE_CURRENT_BINARY_DIR}/glew-${GLEW_VERSION}/bin/Release/${GLEW_PLATFORM}")
    set(GLEW_LIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/glew-${GLEW_VERSION}/lib/Release/${GLEW_PLATFORM}")

    file(GLOB_RECURSE HEADERS "${GLEW_INCLUDES_PATH}/*.h")

    add_library(GLEW::GLEW SHARED IMPORTED GLOBAL ${HEADERS})
    target_include_directories(GLEW::GLEW INTERFACE "${GLEW_INCLUDES_PATH}")
    set_property(TARGET GLEW::GLEW PROPERTY IMPORTED_LOCATION "${GLEW_LIB_PATH}/glew32.lib")
    set_property(TARGET GLEW::GLEW PROPERTY IMPORTED_IMPLIB "${GLEW_BIN_PATH}/glew32.dll")
else ()
    find_package(GLEW REQUIRED GLOBAL)
endif ()

cmake_minimum_required(VERSION 3.22)

project(sklc_lib
    VERSION 0.0.1
    LANGUAGES C CXX
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

if(MSVC)
    add_compile_options(
        /W4 # Enable all warnings.
        # Don't suggest the _s nonsence functions.
        /D_CRT_SECURE_NO_WARNINGS
        /D_CRT_SECURE_NO_WARNINGS_GLOBALS
        /D_CRT_NONSTDC_NO_WARNINGS
    )
else()
    add_compile_options(
        -Wall
        -Werror=return-type
        -Wshadow
        -Wconversion
        -Wno-unused
        -fsanitize=address
        -g
        -D_CRT_SECURE_NO_WARNINGS
    )
endif()

file(GLOB_RECURSE SRCS
    "${PROJECT_SOURCE_DIR}/src/*"
    "${PROJECT_SOURCE_DIR}/src/**"
    "${PROJECT_SOURCE_DIR}/include/*"
    "${PROJECT_SOURCE_DIR}/include/**"
)

#set(OpenGlLibs opengl32)

add_executable(sklc_lib ${SRCS})
set_property(TARGET sklc_lib PROPERTY C_STANDARD 17)
set_property(TARGET sklc_lib PROPERTY CXX_STANDARD 17)
set_property(TARGET sklc_lib PROPERTY C_STANDARD_REQUIRED true)
set_property(TARGET sklc_lib PROPERTY CXX_STANDARD_REQUIRED true)
target_include_directories(sklc_lib PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
)

#target_link_libraries(sklc_lib ${OpenGlLibs})

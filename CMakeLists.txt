cmake_minimum_required(VERSION 3.24)

project(brainfuck C)

# add_subdirectory(common_lib)

add_compile_options(-Wall -Werror)

set(SOURCES
    src/brainfuck.c
)
include_directories(inc)
 
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(-DDEBUG_PRINT)
endif()



add_executable(brainfuck 
    main.c 
    ${SOURCES}
)

enable_testing()
add_subdirectory(tests)
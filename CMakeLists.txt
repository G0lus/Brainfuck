cmake_minimum_required(VERSION 3.24)

project(brainfuck C)

# add_subdirectory(common_lib)

add_compile_options(-Wall -Werror)

set(SOURCES
    src/brainfuck.c
)
include_directories(inc)

add_executable(brainfuck 
    main.c 
    ${SOURCES}
)

# target_include_directories(brainfuck PUBLIC common_lib)
# target_link_libraries(brainfuck vector)

enable_testing()
add_subdirectory(tests)
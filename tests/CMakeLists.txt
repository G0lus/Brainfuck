include_directories(BEFORE ${PROJECT_SOURCE_DIR}/inc)

add_compile_definitions(-DDEBUG_PRINT)
add_executable(bf_tests 
    tests.c
    ${PROJECT_SOURCE_DIR}/src/brainfuck.c
)


add_test("Brainfuck testing" bf_tests)


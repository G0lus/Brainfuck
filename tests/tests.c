#include <assert.h>
#include <stdio.h>

#include "brainfuck.h"

int test_adding(void){
    const char code[] = "+++";
    size_t code_len = sizeof(code) / sizeof(char);
    unsigned char ret = bf_process_code(code_len, code);
    printf("ret %d\n", ret);
    assert(ret == 3);
    bf_clear_all();
    return 0;
}

int test_decrease(void){
    const char code[] = "---";
    size_t code_len = sizeof(code) / sizeof(char);
    unsigned char ret = bf_process_code(code_len, code);
    printf("ret %d\n", ret);
    assert(ret == 253);
    bf_clear_all();
    return 0;
}

int test_next_cell(void){
    const char code[] = "+++>";
    size_t code_len = sizeof(code) / sizeof(char);
    unsigned char ret = bf_process_code(code_len, code);
    printf("ret %d\n", ret);
    assert(ret == 0);
    bf_clear_all();
    return 0;
}

int test_previous_cell(void){
    const char code[] = "++>++++><";
    size_t code_len = sizeof(code) / sizeof(char);
    unsigned char ret = bf_process_code(code_len, code);
    printf("ret %d\n", ret);
    assert(ret == 4);
    bf_clear_all();
    return 0;
}

int test_single_loop(void){
    const char code[] = "++[>++<-]>";
    size_t code_len = sizeof(code) / sizeof(char);
    unsigned char ret = bf_process_code(code_len, code);
    printf("ret %d\n", ret);
    assert(ret == 4);
    bf_clear_all();
    return 0;
}

int test_more_loops(void){
    const char code[] = "++[>++[>++<-]<-]>>";
    size_t code_len = sizeof(code) / sizeof(char);
    unsigned char ret = bf_process_code(code_len, code);
    printf("ret %d\n", ret);
    assert(ret == 8);
    bf_clear_all();
    return 0;
}

int main(void){
    assert(test_adding() == 0);
    assert(test_decrease() == 0);
    assert(test_next_cell() == 0);
    assert(test_previous_cell() == 0);
    assert(test_single_loop() == 0);
    assert(test_more_loops() == 0);
    
    return 0;
}
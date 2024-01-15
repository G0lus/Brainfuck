#ifndef BRAINFUCK_H__
#define BRAINFUCK_H__

#include <stdlib.h>

/**
 * @brief Processes all the code provided.
 * @param code_len
 * @param code
 * @retval Value of the cell pointed to at the end of the code. Return value only for testing purposes.
*/
unsigned char bf_process_code(const size_t code_len, const char code[code_len]);

#endif
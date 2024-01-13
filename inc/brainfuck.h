#ifndef BRAINFUCK_H__
#define BRAINFUCK_H__

#include <stdlib.h>

enum bf_state{
    BF_STATE_NEXT_CELL,
    BF_STATE_PREV_CELL,
    BF_STATE_INC_VAL,
    BF_STATE_DEC_VAL,
    BF_STATE_PRINT,
    BF_STATE_SCAN,
    BF_STATE_LOOP_START,
    BF_STATE_LOOP_END,
    BF_STATE_ERROR,
};

/**
 * @brief Processes all the code provided.
 * @param code_len
 * @param code
 * @retval Value of the cell pointed to at the end of the code.
*/
unsigned char bf_process_code(const size_t code_len, const char code[code_len]);

/**
 * @brief Clears internal cells value, etc. Used for testing purposes.
*/
void bf_clear_all(void);

#endif
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "brainfuck.h"

#define CELLS_NUM (30 * 1024UL)
#define LOOPS_MAX_NUM (256U)

#define BF_CHAR_INC_VAL '+'
#define BF_CHAR_DEC_VAL '-'
#define BF_CHAR_INC_CELL '>'
#define BF_CHAR_DEC_CELL '<'
#define BF_CHAR_START_LOOP '['
#define BF_CHAR_STOP_LOOP ']'
#define BF_CHAR_PRINT '.'
#define BF_CHAR_SCAN ','

/** Go through the code one char at the time. There is no need to parse it.
 * '+' increases the value in the cell.
 * '-' decreases the value in the cell.
 * '>' moves ptr to next cell.
 * '<' moves ptr to previous cell.
 * '[' starts the loop or provided that cell value is 0 jumps to loop end.
 * ']' ends the loop
 * otherwise loops back to the start of the loop.
 */

unsigned char bf_process_code(const size_t code_len, const char code[code_len])
{
    unsigned char cells[CELLS_NUM] = {0};
    size_t cell_num = 0;

    for (size_t i = 0; i < code_len && code[i] != '\0'; i++)
    {

#ifdef DEBUG_PRINT
        printf("BF STATE: %c\n", code[i]);
#endif
        switch (code[i])
        {
        case BF_CHAR_INC_VAL:
            cells[cell_num]++;
            break;
        case BF_CHAR_DEC_VAL:
            cells[cell_num]--;
            break;
        case BF_CHAR_INC_CELL:
            cell_num = cell_num == CELLS_NUM ? 0 : cell_num + 1;
            break;
        case BF_CHAR_DEC_CELL:
            cell_num = cell_num == 0 ? CELLS_NUM : cell_num - 1;
            break;
        case BF_CHAR_SCAN:
            printf("Provide input: \t");
            scanf("%c", &cells[cell_num]);
            printf("%c", cells[cell_num]);
            break;
        case BF_CHAR_PRINT:
            printf("%c", cells[cell_num]);
            break;
        case BF_CHAR_START_LOOP:
            if (cells[cell_num] == 0)
            {
                size_t open_bracket = 1;
                while (open_bracket > 0 && i < code_len)
                {
                    i++;
                    if (code[i] == BF_CHAR_START_LOOP)
                    {
                        open_bracket++;
                    }
                    if (code[i] == BF_CHAR_STOP_LOOP)
                    {
                        open_bracket--;
                    }
                }
            }
            break;
        case BF_CHAR_STOP_LOOP:
            if (cells[cell_num] != 0)
            {
                size_t close_bracket = 1;
                while (close_bracket > 0 && i < code_len)
                {
                    i--;
                    if (code[i] == BF_CHAR_STOP_LOOP)
                    {
                        close_bracket++;
                    }
                    if (code[i] == BF_CHAR_START_LOOP)
                    {
                        close_bracket--;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    return cells[cell_num];
}
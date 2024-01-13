#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "brainfuck.h"

#define CELLS_NUM 30000UL
#define LOOPS_MAX_NUM 256U

#ifdef DEBUG_PRINT
static char* states_str[] = {
    "BF_STATE_NEXT_CELL",
    "BF_STATE_PREV_CELL",
    "BF_STATE_INC_VAL",
    "BF_STATE_DEC_VAL",
    "BF_STATE_PRINT",
    "BF_STATE_SCAN",
    "BF_STATE_LOOP_START",
    "BF_STATE_LOOP_END",
    "BF_STATE_LOOP_SKIP",
    "BF_STATE_ERROR",
};
#endif
static unsigned char cells[CELLS_NUM];
static size_t cell_num;
static bool loop_skip = false;
static size_t loops_start_idx[LOOPS_MAX_NUM];
static size_t loops_idx;


/** Go through the code one char at the time. There is no need to parse it. 
   * '+' increases the value in the cell.
   * '-' decreases the value in the cell.
   * '>' moves ptr to next cell.
   * '<' moves ptr to previous cell.
   * '[' starts the loop or provided that cell value is 0 jumps to loop end.
   * ']' ends the loop 
   * otherwise loops back to the start of the loop.
  */

static enum bf_state bf_get_state(const char ch){
  enum bf_state state = BF_STATE_ERROR;
  switch(ch){
    case '+':
      state = BF_STATE_INC_VAL;
      break;
    case '-':
      state = BF_STATE_DEC_VAL;
      break;
    case '>':
      state = BF_STATE_NEXT_CELL;
      break;
    case '<':
      state = BF_STATE_PREV_CELL;
      break;
    case '.':
      state = BF_STATE_PRINT;
      break;
    case ',':
      state = BF_STATE_SCAN;
      break;
    case '[': 
      state = BF_STATE_LOOP_START;
      break;
    case ']': 
      state = BF_STATE_LOOP_END;
      break;
    default:
      state = BF_STATE_ERROR;
      break;
  }
  return state;
}


unsigned char bf_process_code(const size_t code_len, const char code[code_len]){
  enum bf_state state;
  for(size_t i = 0; i < code_len && code[i] != '\0'; i++){
    state = bf_get_state(code[i]);
    #ifdef DEBUG_PRINT
    printf("BF STATE: %s\n", states_str[state]);
    #endif
    switch(state){
      case BF_STATE_INC_VAL:
        cells[cell_num]++;
        break;
      case BF_STATE_DEC_VAL:
        cells[cell_num]--;
        break;
      case BF_STATE_NEXT_CELL:
        cell_num = cell_num == CELLS_NUM ? 0 : cell_num + 1;
        break;
      case BF_STATE_PREV_CELL:
        cell_num = cell_num == 0 ? CELLS_NUM : cell_num - 1;
        break;
      case BF_STATE_SCAN:
        printf("Provide input: \t");
        scanf("%c", &cells[cell_num]);
        printf("%c", cells[cell_num]);
        break;
      case BF_STATE_PRINT:
        printf("%c", cells[cell_num]);
        break;
      case BF_STATE_LOOP_END:
        if(cells[cell_num] != 0 && loops_idx > 0){
          i = loops_start_idx[loops_idx - 1] - 1;
        }
        loops_start_idx[loops_idx - 1] = 0;
        loops_idx--;
        break;
      case BF_STATE_LOOP_START:
        if(loops_start_idx[loops_idx - 1] != i){
          loops_start_idx[loops_idx] = i;
          loops_idx++;
        }
        break;
      default:
        break;
    }
  }
  return cells[cell_num];
}

void bf_clear_all(void){
  for(size_t i = 0; i < cell_num + 1; i++){
    cells[i] = 0;
  }
  loop_skip = false;
  cell_num = 0;
}
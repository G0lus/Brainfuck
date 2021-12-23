#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define arr_size(arr, type) sizeof(arr)/sizeof(type)
#define ARR_BASE_SIZE 8

void show_cells(int num_cells, uint32_t arrow_cell, uint8_t* num_arr, uint32_t arr_size){
  if(num_cells > arr_size){
    fprintf_s(stderr, "Cannot print more numbers than there are defined \n");
    num_cells = arr_size;
  }
  if (arrow_cell >= num_cells){
    fprintf_s(stderr, "Arrow set to last cell\n");
    arrow_cell = num_cells - 1;
  }
  for (int i = 0; i < num_cells; i++)
  {
    if(i == 0)
      printf_s("\n\t _________");

    printf_s("\n\t|         |");
    printf_s("\n%d\t|   %.3d   |", i, *(num_arr + i));
    if(i == arrow_cell)
      printf_s("  <---");
    printf_s("\n\t|_________|");
  }
}

// void examine_cmd(char cmd, )

/**
 * TODO:
 *  - interpreting each command in brainfck
 *  - securing input -> if more cells than allocated -> allocate more
 *  - reading code from file
 *  - writing output to file
 *  - reading code from program argument
 *  - reading code from input as a line and single command
 *  - stepping through code
 *  - running full code
 *  - clear terminal after each instruction
 * */

int main(int argc, char** argv){
  char cmd;
  
  
  uint8_t arrow = 0; // arrow in 5th cell
  uint8_t* cells = calloc(ARR_BASE_SIZE, sizeof(uint8_t));
  do{
    uint8_t* cell_ptr = cells + arrow;
    show_cells(ARR_BASE_SIZE, arrow, cells, ARR_BASE_SIZE);
    printf_s("\nInput brainfck instruction:\t");
    scanf("%c", &cmd);
    fflush(stdin);
    switch (cmd)
    {
      case '.':     // output to terminal
        break;
      case ',':     // input from terminal
        break;
      case '>':     // next cell
        if(arrow+1 >= ARR_BASE_SIZE)
          arrow = 0;
        else
          arrow++;
        break;
      case '<':     // previous cell
        if(arrow-1 < 0)
          arrow = ARR_BASE_SIZE-1;
        else
          arrow--;
        break;
      case '+':     // increment cell's value
        (*cell_ptr)++;
        break;
      case '-':     // decrement cell's value
        (*cell_ptr)--;
        break;
      case '[':     // open loop
        break;
      case ']':     // close loop
        break;
      case 'q':
        break;
      default:
        fprintf_s(stderr, "Unknown cmd: available '<' '>' ',' '.' '+' '-' '[' ']'\n");
        fflush(stdin);
        system("pause");
        break;
    }
    system("cls");
  }while(cmd != 'q');
  return 0;
}
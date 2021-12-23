#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define arr_size(arr, type) sizeof(arr)/sizeof(type)
#define ARR_BASE_SIZE 8

#define INTERPRETER_TYPE_ONE 0      // Sort of REPL (Read-Eval-Print-Loop)
#define INTERPRETER_TYPE_LINE 1     // Interpreting a line of code
#define INTERPRETER_TYPE_FILE 2     // Interpreting a file with code

void show_cells(int num_cells, uint32_t arrow_cell, uint8_t* num_arr, uint32_t arr_size){
  if(num_cells > arr_size){
    fprintf(stderr, "Cannot print more numbers than there are defined \n");
    num_cells = arr_size;
  }
  if (arrow_cell >= num_cells){
    fprintf(stderr, "current_cell_num  set to last cell\n");
    arrow_cell = num_cells - 1;
  }
  for (int i = 0; i < num_cells; i++)
  {
    if(i == 0)
      printf("\n\t _________");

    printf("\n\t|         |");
    printf("\n%d\t|   %.3d   |", i, *(num_arr + i));
    if(i == arrow_cell)
      printf("  <---");
    printf("\n\t|_________|");
  }
}

char examine_cmd(char cmd, uint8_t* current_cell_ptr, uint8_t* current_cell_num){
  char input;
  if(isspace(cmd)){
    return 0;
  }
  switch (cmd)
  {
    case '.':     // output to terminal
      return *(current_cell_ptr);
    case ',':     // input from terminal
      printf("Provide input:\t");
      scanf("%c", &input);
      fflush(stdin);
      *current_cell_ptr = input;
      input = 0;
      break;
    case '>':     // next cell
      if(*current_cell_num +1 >= ARR_BASE_SIZE)
        *current_cell_num  = 0;
      else
        (*current_cell_num) += 1;
      break;
    case '<':     // previous cell
      if(*current_cell_num -1 < 0)
        *current_cell_num  = ARR_BASE_SIZE-1;
      else
        (*current_cell_num) --;
      break;
    case '+':     // increment cell's value
      (*current_cell_ptr)++;
      break;
    case '-':     // decrement cell's value
      (*current_cell_ptr)--;
      break;
    case '[':     // open loop

      break;
    case ']':     // close loop
      break;
    case 'q':
      break;
    default:
      fprintf(stderr, "\nUnknown cmd: available '<' '>' ',' '.' '+' '-' '[' ']'\n");
      fflush(stdin);
      system("pause");
      break;
  }
  return 0;
}

void out_cell(uint8_t* const cell, char* out_arr){
  printf("%c", *cell);
}
/**
 * TODO:
 *  - interpreting each command in brainfck
 *  - securing input -> if more cells than allocated -> allocate more
 *  x reading code from file
 *  - writing output to file
 *  - reading code from program argument
 *  - reading code from input as a line and single command
 *  - stepping through code
 *  - running full code
 *  x clear terminal after each instruction
 * */

int main(int argc, char* argv[]){
  char cmd, input;
  uint8_t current_cell_num  = 0, output_size = 0; 
  uint8_t* cells = calloc(ARR_BASE_SIZE, sizeof(uint8_t));
  char* output_ptr = calloc(ARR_BASE_SIZE, sizeof(char));
  uint8_t* current_cell_ptr;
  FILE* bf_program = NULL;
  uint8_t interpreter_type = INTERPRETER_TYPE_ONE;

  if(argc > 1){
    char* type = strtok(argv[1],"-");
    if(!strcmp(type, "f")){
      interpreter_type = INTERPRETER_TYPE_FILE;
      const char* filename = argv[2];
      bf_program = fopen(filename, "r");
      if(bf_program == NULL)
        fprintf(stderr, "Unable to open file %s\n", filename);
      else
        fprintf(stdout, "File %s opened\n", filename);
    }
    else if(type == "l"){
      interpreter_type = INTERPRETER_TYPE_LINE;
    }
  }

  if(interpreter_type == INTERPRETER_TYPE_ONE){
    do{
      system("cls");
      
      if(output_size > 0){
        printf("\nOutput:\t");

        for(int i = 0; i < output_size; i++){
          printf("%c", *(output_ptr - output_size + i));
        }
          printf("\n");
      }
      fflush(stdout);

      current_cell_ptr = cells + current_cell_num;
      show_cells(ARR_BASE_SIZE, current_cell_num, cells, ARR_BASE_SIZE);

      printf("\nInput brainfck instruction:\t");
      scanf("%c", &cmd);
      fflush(stdin);
      *output_ptr = examine_cmd(cmd, current_cell_ptr, &current_cell_num);
      if(output_ptr != 0){
        output_ptr ++;
        output_size ++;
      }
    }while(cmd != 'q');
  }  
  else{
    cmd = getc(bf_program);
    while(cmd != EOF){
      current_cell_ptr = cells + current_cell_num ;
      *output_ptr = examine_cmd(cmd, current_cell_ptr, &current_cell_num);
      if(*output_ptr != 0){
        output_ptr ++;
        output_size ++;
      }
      cmd = getc(bf_program);
    }
    if(output_size > 0){
      printf("\nOutput:\t");

      for(int i = 0; i < output_size; i++){
        printf("%c", *(output_ptr - output_size + i));
      }
      printf("\n");
    }
    show_cells(ARR_BASE_SIZE, current_cell_num, cells, ARR_BASE_SIZE);
  }
  exit(EXIT_SUCCESS);
}
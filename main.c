#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "brainfuck.h"

#define ARGC_MINIMUM 2U
#define VECTOR_LOOP_START_NUM 16U

/* Argument can be either name of the fie with code or code itself. */
enum arg_type{
  ARG_TYPE_FILE,
  ARG_TYPE_CODE,
  ARG_TYPE_UNKNOWN,
  ARG_TYPE_NONE,
};


static size_t file_get_length(FILE* file){
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    return length;
}

static enum arg_type get_arg_type(int argc, char* argv){
  if(argc <= ARGC_MINIMUM){
    return ARG_TYPE_NONE;
  }
  char* type = strtok(argv, "-");
  if(!strcmp(type, "f")){
    return ARG_TYPE_FILE;
  }
  else if(!strcmp(type, "l")){
    return ARG_TYPE_CODE;
  }
  else{
    return ARG_TYPE_UNKNOWN;
  }
}

int main(int argc, char* argv[]){
  int exit_status = EXIT_SUCCESS;
  char* program_buffer = NULL;
  size_t program_buffer_len = 0;

  // If argument is provided, interpret it based on type:
  // "-f" -> file (2nd argument is file's name)
  enum arg_type arg = get_arg_type(argc, argv[1]);
  #ifdef DEBUG_PRINT
  printf("arg_type -> %d\n", arg);
  #endif
  /**
   * First we need to check whether the code is provided via the file or 
   * command line. 
   * If provided via file, hence ARG_TYPE_FILE:
   *  * Open and check the length of file. No need to parse it. 
   *  * Allocate the length of the file.
   *  * Read all code to memory.
   * If provided via command line, hence ARG_TYPE_CODE:
   *  * Check the length of code
   *  * Allocate the length.
   *  * Read the code to memory.
   * If there is wrong arhument or none exit the program.
   * */

  if(arg == ARG_TYPE_NONE){
    fprintf(stderr, "2nd argument not provided\n");
    return EXIT_FAILURE;
  }
  else if(arg == ARG_TYPE_FILE){
    char* filename = argv[2];
    FILE* file_program = fopen(filename, "r");
    if(file_program == NULL){
      fprintf(stderr, "Cannot open file %s\n", filename);
      exit_status = EXIT_FAILURE;
      goto EXIT;
    }
    size_t file_len = file_get_length(file_program);
    program_buffer = calloc(file_len, sizeof(char));
    if(!program_buffer){
      fprintf(stderr, "Not enough memory to allocate %lu of memory\n", file_len);
      exit_status = EXIT_FAILURE;
      goto EXIT;
    }
    program_buffer_len = file_len;
    #ifdef DEBUG_PRINT
    printf("Allocated %ld bytes\n", file_len);
    #endif
    if(fread(program_buffer, sizeof(char), file_len, file_program) != file_len){
      fprintf(stderr, "Error reading %lu bytes from %s\n", file_len, filename);
      exit_status = EXIT_FAILURE;
      goto EXIT;
    }
    fclose(file_program);
  }
  else if(arg == ARG_TYPE_CODE){
    char* program = argv[2];
    size_t program_len = strlen(program);
    program_buffer = calloc(program_len, sizeof(char));
    if(!program_buffer){
      fprintf(stderr, "Not enough memory to allocate %lu of memory", program_len);
      exit_status = EXIT_FAILURE;
      goto EXIT;
    }
    strncpy(program_buffer, program, program_len);
    program_buffer_len = program_len;
  }
  else{
    fprintf(stderr, "2nd argument not correct.\n");
    exit_status = EXIT_FAILURE;
    goto EXIT;
  }
  #ifdef DEBUG_PRINT
  printf("Read %ld bytes: %s\n", program_buffer_len, program_buffer);
  #endif
  
  bf_process_code(program_buffer_len, program_buffer);
  

  EXIT:
  free(program_buffer);
  return exit_status;
}
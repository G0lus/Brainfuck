#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BUF_SIZE 4096   // 4kB
#define CELLS_NUM 256   // 256B


int main(int argc, char* argv[]){

  char* chBufferProgram = calloc(BUF_SIZE, sizeof(char));
  if(!chBufferProgram){
    fprintf(stderr, "Not enough memory to allocate %u of memory", BUF_SIZE);
  }

  uint32_t u32StartBuffPtr = (uint32_t) chBufferProgram;

  uint8_t* u8CellsPtr = calloc(CELLS_NUM, sizeof(uint8_t));
  if(!u8CellsPtr){
    fprintf(stderr, "Not enough memory to allocate %u of memory", CELLS_NUM * sizeof(uint8_t));
  }
  uint32_t u32StartCellsPtr = (uint32_t) u8CellsPtr;
  FILE* fileProgram = NULL;

  // If argument is provided, interpret it based on type:
  // "-f" -> file (2nd argument is file's name)
  if(argc > 1){
    char* type = strtok(argv[1],"-");
    if(!strcmp(type, "f")){
      const char* filename = argv[2];
      fileProgram = fopen(filename, "r");
      if(fileProgram == NULL)
        fprintf(stderr, "Unable to open file %s\n", filename);
      else
        fprintf(stdout, "File %s opened\n", filename);
    }
    else if(!strcmp(type, "l")){
      strncpy(chBufferProgram, argv[2], BUF_SIZE);
    }
  }
  else{
    fprintf(stderr, "2nd argument not provided");
    free(fileProgram);
    free(chBufferProgram);
    free(fileProgram);
    free(u8CellsPtr);
  }

  uint64_t u64FileLength = 0;
  uint64_t u64ChunksNum = 0;
  uint64_t u64BytesRead = 0;
  
  if(fileProgram != NULL){
    
    fseek(fileProgram, 0, SEEK_END);
    u64FileLength = ftell(fileProgram);
    fseek(fileProgram, 0, SEEK_SET);
    

    // calculate how much chunks there needs to be (each 4kB of memory)
    u64ChunksNum = (uint64_t) ceil((double) u64FileLength / (double)BUF_SIZE);
    if(u64ChunksNum > 1){
        chBufferProgram = realloc(chBufferProgram, u64ChunksNum*BUF_SIZE*sizeof(char));
      if(chBufferProgram == NULL){
        fprintf(stderr, "Problem reallocing array");
      }
    }
    
    u64BytesRead = fread(chBufferProgram, sizeof(char), u64ChunksNum * BUF_SIZE - 1, fileProgram);

    if(ferror(fileProgram)){
      perror("Error ocurred while reading a file: ");
    }
    
    if(u64BytesRead < BUF_SIZE)
      *(chBufferProgram + u64BytesRead + 1) = '\0';
  }
  else{
    u64ChunksNum = 1;
  }

  
  uint64_t i=0, j=0;
  uint8_t n = 0;
  uint16_t u16LoopCnt=0;
  while(j != u64ChunksNum){
    for(;*chBufferProgram != '\0' ; chBufferProgram++){
      switch(*chBufferProgram){
        case '+':
          (*u8CellsPtr)++;
          break;
        case '-':
          (*u8CellsPtr)--;
          break;
        case '>':
          n++;
          u8CellsPtr = ((uint8_t*) u32StartCellsPtr) + n;
          break;
        case '<':
          n--;
          u8CellsPtr = ((uint8_t*) u32StartCellsPtr) + n;
          break;
        case '.':
          fprintf(stdout, "%c",*u8CellsPtr);
          break;
        case ',':
          fprintf(stdin, "Provide input\t");
          scanf("%c", u8CellsPtr);
          break;
        case '[':
          u16LoopCnt++;
          if(*u8CellsPtr == 0){
            while(*chBufferProgram != ']'){
              chBufferProgram++;
            }
          }
          break;
        case ']':
          if(*u8CellsPtr != 0){
            do{
              chBufferProgram--;
            }while(*chBufferProgram != '[' && u16LoopCnt > 0);
            chBufferProgram--;
          }
          u16LoopCnt--;
          break;
      }
    }
    j++;
  }


  
  
  
  free(fileProgram);
  free(chBufferProgram);
  free(u8CellsPtr);
  fclose(fileProgram);
  exit(EXIT_SUCCESS);
}
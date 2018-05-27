// Write function equal to: head -n 10
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("Invalid number of arguments");
        exit(-1);
    }

    int read;
    long unsigned int n = 0;
    char *line = NULL;
    
    FILE *stream;
    stream = fopen(argv[1],"r"); 
    
    if (stream == NULL) {
        printf("File failed to open\n");
        exit(1);
    }
    
    int line_counter = 0;
    int char_counter = 0;
    int word_counter = 0;
    while ((read = getline(&line,&n,stream)) != -1) {
      line_counter += 1;
      
      int cnt = 0;
      while (line[cnt] != '\n') {
          if (line[cnt] == ' ' && cnt != 0 && 
              line[cnt -1] != ' ' && line[cnt+1] != '\n') {
              word_counter += 1;
          }
          char_counter +=1;
          cnt += 1;
      }
      if (line[cnt] == '\n' ) { 
         char_counter += 1;
         if (cnt > 0 && line[cnt-1] != ' ')
            word_counter += 1;
      }
    }

    printf("%d %d %d\n", line_counter, word_counter, char_counter);
    free(line);
    fclose(stream);
    exit(0);
}








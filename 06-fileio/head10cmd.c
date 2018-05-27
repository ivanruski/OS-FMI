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
    
    short counter = 0;

    while ((read = getline(&line,&n,stream)) != -1) {
      if (counter == 10)
          break;

      printf("%s", line);
      counter += 1;
    }

    free(line);
    fclose(stream);

    exit(0);
}

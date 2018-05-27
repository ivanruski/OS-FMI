// Write function that swaps content of two files

#include <err.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void randomFileName(char *name, int n){

    for (int i = 0; i < n; i++) {
        name[i] = ( (rand() % 26) + 97 );
    }
}

int main(int argc, char* argv[]) 
{
    srand(time(NULL));
    if (argc != 3) {
        printf("Invalid number of arguments");
        exit(-1);
    }

    const int fd1 = open(argv[1], O_RDWR);
    if (fd1 == -1) {
        printf("%s failed to open", argv[1]);
        exit(1);
    }
   
    const int fd2 = open(argv[2], O_RDWR);
    if (fd2 == -1) {
        close(fd1);
        printf("%s failed to open", argv[2]);
        exit(1);
    }
    
    char *randName = malloc(15);
    randomFileName(randName,15);

    const int fd3 = open(randName, O_CREAT | O_RDWR | O_TRUNC,0777);
    if (fd3 == -1) {       
      close(fd1);
      close(fd2);
      free(randName);
      printf("Something went wrong please try again");
    }
    
    char c[4096];
    ssize_t read_size;
    
    
    while ((read_size = read(fd1, &c, sizeof(c))) > 0) {
         if (write(fd3,&c, read_size) != read_size ) {      
            close(fd1);
            close(fd2);
            close(fd3);
            err(1, "error while writing to fd3");
            
         };
    }   
   
    lseek(fd1,0,SEEK_SET);

    while ((read_size = read(fd2, &c, sizeof(c))) > 0 ) {
         if(write(fd1,&c, read_size) != read_size){
             close(fd1);
             close(fd2);
             close(fd3);
             err(1, "error while wrting to fd1");
         }
    }   

    lseek(fd2,0,SEEK_SET);
    lseek(fd3,0,SEEK_SET);
    while ((read_size = read(fd3, &c, sizeof(c))) > 0) {
         if(write(fd2,&c, read_size) != read_size) {
             close(fd1);
             close(fd2);
             close(fd3);
             err(1, "error while wrigng to fd2");
         }
    }   

    close(fd1);
    close(fd2);
    close(fd3);
    remove(randName); 
    free(randName);
    exit(0);
}








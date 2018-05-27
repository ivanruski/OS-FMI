// Cat command

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        printf("At least one file is required\n");
        exit(-1);
    }

    struct stat f;
    for (int i = 1; i < argc; i++) {
         if (stat(argv[i],&f) == -1){
            err(1,"%s failed to open\n", argv[i]);
         }
         
         if (S_ISREG(f.st_mode) == 0){
            errx(1, "%s is not a regular file\n",argv[i]);
         }      
    }

    int fds[argc - 1];
    char buffer[4096];
    int rd_s;
    for (int i = 1; i < argc; i++) {
       fds[i-1] = open(argv[i], O_RDONLY);
       if (fds[i-1] == -1) {
           err(1,"%s failed to open", argv[i]);
       }
       while ((rd_s = read(fds[i-1], &buffer, sizeof(buffer))) > 0) {
           write(1,&buffer, rd_s);
       }
       close(fds[i-1]);
    }
    exit(0);
}








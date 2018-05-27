// wait command to execute

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   if (argc != 4) {
       errx(1,"Usage: <cmd> <cmd> <filename>");
   }

   struct stat f;
   if (stat(argv[3],&f) == 0){
       if (S_ISDIR(f.st_mode)) {
           errx(1,"%s is a directory", argv[3]);
       }
   }
   int codes[argc-2];
   for (int i = 1; i < argc -1; i++) {
       int cpid = fork();
       
       if (cpid > 0) {
           int status;
           wait(&status);
           codes[i-1] = WEXITSTATUS(status);
       }
       else {
           if (execlp(argv[i],argv[i],'\0') == -1) {
               exit(errno);
           }
       }
   }

   if (codes[0] != 0) {
       exit(1);
   }

   const int fd = open(argv[3], O_CREAT | O_RDWR | O_TRUNC,0777);
   int write_size = strlen(argv[1]);
   int written;
   if ((written = write(fd, argv[1], write_size)) != write_size){
       err(1, "unsuccessful write into %s", argv[1]);
   }
   write(fd,"\n",1);
   close(fd);
   exit(0);


}

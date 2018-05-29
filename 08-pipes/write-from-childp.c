// Basic pipe example

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
   if (argc != 2) {
      errx(1,"Usage: <filename>");   
   }
   
   struct stat s;
   if (stat(argv[1],&s) == 0) {
       if (S_ISDIR(s.st_mode)){
           errx(1,"%s is a directory", argv[1]);
       }
   }

   char *str1 = "foo\n";
   char *str2 = "bar\n";

   int fd = open(argv[1],O_CREAT | O_RDWR | O_TRUNC, 0777);
   write(fd,str1,2);
   
   pid_t cpid = fork();
   if (cpid == -1) {
       err(1,"fork failed");
   }
   
   if (cpid == 0) {//child process
       if (write(fd,str2,strlen(str2)) == -1) {
           close(fd);
           err(1,"child failed to write");
       }
       close(fd);
   } else {
       int status;
       wait(&status);
      
       if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
           write(fd,str1+2,2);
           close(fd);
       } else {
           err(1, "Child process failed");
       }

       exit(0);
   }
}

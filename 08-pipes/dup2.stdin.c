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
      errx(1,"Usage: <string>");   
   }
   
   int fds[2];
   if (pipe(fds) == -1) {
       err(1,"pipe filed");
   }

   pid_t cpid = fork();
   if (cpid == -1) {
       err(1, "fork failed");
   }

   if (cpid == 0) {
       dup2(fds[0],0);
       close(fds[1]);
       if (execlp("wc", "wc", "-c", '\0') == -1) {
           err(1, "wc failed to execlp");
       }
   }
   
   close(fds[0]);
   write(fds[1],argv[1], strlen(argv[1]));
   close(fds[1]);
   wait(NULL);
   exit(0);
}








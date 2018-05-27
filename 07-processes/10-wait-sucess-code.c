// wait command to execute

#include <err.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   if (argc != 3) {
       errx(1,"usage: <cmd1> <cmd2>");
   }

   int cpid = fork();
   if (cpid == 0) {
       execlp(argv[1],argv[1],'\0');
   }
   
   int status;
   wait(&status);

   if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      exit(1);
   }

   if (execlp(argv[2], argv[2], '\0') == -1) {
       err(1, "%s failed to execute", argv[2]);
   }
}

// wait command to execute

#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   if (argc != 2) {
       errx(1,"Please provide command name");
   }

   int child_pid = fork();

   if (child_pid == 0) {
       if(execlp(argv[1], argv[1], (char *)NULL) == -1) {
           err(1, "%s failed to execute\n", argv[1]);
       }
   }

   int status;
   wait(&status);

   if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
       printf("%s\n",argv[1]);
   }

   exit(0);
}

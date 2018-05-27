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
#include <signal.h>

int main(int argc, char *argv[]) {
   if (argc < 2) {
       errx(1,"at least one command");
   }

   int codes[argc-1];
   for (int i = 1; i < argc; i++) {
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

   for (int i = 0; i < argc-1; i++) {
       printf("cmd: %s   status-code: %d\n",argv[i+1],codes[i]);
   }
   exit(0);
}

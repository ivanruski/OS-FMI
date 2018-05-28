// Wait first child pid which has executed succesfully.
// If both of it are unsuccessfull print -1

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
   if (argc != 3) {
       errx(1,"Usage: <cmd> <cmd>");
   }

   int cpid1 = fork();
   if (cpid1 == 0) {
       if (execlp(argv[1],argv[1],'\0') == -1) {
           exit(1);
       };
   }

   int cpid2 = fork();
   if (cpid2 == 0) {
       if (execlp(argv[2],argv[2],'\0') == -1) {
           exit(1);  
       } 
   }
   
   int status;
   int finished_pid = wait(&status);
   
   if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
       printf("%d\n",finished_pid);
   }
   else {
       finished_pid = wait(&status);
       if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
           printf("%d\n",finished_pid);
       }
       else {
           printf("-1\n");
       }
   }

   //printf("cpid1: %d\ncpid2: %d",cpid1,cpid2);
   exit(0);
}

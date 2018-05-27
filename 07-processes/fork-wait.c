// wait command to execute

#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   if (argc != 4) {
       errx(1,"3 commands without arguments are required");
   }

   int c_pid = fork();

   if (c_pid == 0) {
       if(execlp(argv[1], argv[1], (char *)NULL) == -1) {
           err(1, "%s failed to execute\n", argv[1]);
       }
   }

   int status;
   wait(&status);

   printf("status: %d  pid_id: %d\n",WEXITSTATUS(status), c_pid);
   
   c_pid = fork();
   
   if (c_pid == 0) {
       if(execlp(argv[2], argv[2], (char *)NULL) == -1) {
           err(1, "%s failed to execute\n", argv[2]);
       }
   }

   wait(&status);
   printf("status: %d  pid_id: %d\n",WEXITSTATUS(status), c_pid);
   
   c_pid = fork();
   
   if (c_pid == 0) {
       if(execlp(argv[3], argv[3], (char *)NULL) == -1) {
           err(1, "%s failed to execute\n", argv[3]);
       }
   }

   wait(&status);
   printf("status: %d  pid_id: %d\n",WEXITSTATUS(status), c_pid);
 
   exit(0);
}

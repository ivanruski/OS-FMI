// Execute date command

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() 
{
   pid_t child_pid = fork();
   
   if (child_pid == 0) {
      write(1,"going to sleep\n",16);

      if (execl("/bin/sleep","sleep","10", (char *)NULL) == -1) {
          err(1, "Sleep failed to execute");
      }
   }

   wait(NULL);
   printf("awaken\n");
    
   exit(0);
}








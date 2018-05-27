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
   unsigned short child_pid = fork();
   
   if (child_pid == 0) {
     for (int i = 0; i < 100000; i++) {
         write(0,"child\n",6);
     }
     exit(0);
   }

   for (int i = 0; i < 100000; i++) {
       printf("parent\n");
   }
   
   exit(0);
}








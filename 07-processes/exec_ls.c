// Execute date command

#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
   if (argc != 2) {
      errx(1, "Please provide one argument for ls");
   }

   if (strlen(argv[1]) > 2) {
      errx(1, "Only one arugment for ls");
   }

   if (execl("/bin/ls", "ls",argv[1], (char *)NULL) == -1) {
      err(1, "ls command failed to execute\n");
   }

   exit(0);
}








// Execute date command

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
   if (execl("/bin/date", "date", (char *)NULL) == -1) {
      err(1, "Date command failed to execute\n");
   }

   exit(0);
}








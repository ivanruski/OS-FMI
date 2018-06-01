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
#include <stdint.h>


int main(int argc, char *argv[]) {
   
   if (argc != 2) {
      errx(1,"Usage: <filename>");   
   }

   const int fd = open(argv[1], O_RDONLY);
   if (fd == -1) {
     err(1,"opening %s failed",argv[1]);
   }

   uint8_t buf;
   unsigned int counter[256];

   for(int i = 0; i < 256; i++) {
     counter[i] = 0;
   }
   
   while (read(fd,&buf,1) > 0){
     counter[buf]++;
   }
   close(fd);
   
   for (int i = 0; i < 256; i++) {
     printf("%x -> %d\n",i,counter[i]);
   }




   


   
   exit(0);
}








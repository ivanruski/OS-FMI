// Find the biggest byte from binary file

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[]) 
{
   if (argc != 2) {
       
      errx(1,"<path_to_binary_file>\n");
   }

   struct stat f_stat;
   if (stat(argv[1], &f_stat) == -1) {
      err(1, "%s file failed to open\n", argv[1]);
   }

   if (S_ISREG(f_stat.st_mode) == 0) {
      errx(1, "%s file is not a regular file\n", argv[1]);
   }

   FILE *f = fopen(argv[1], "r+b");
   short read_size;
   uint8_t read_value;
   uint8_t max_byte;
   while ((read_size = fread(&read_value,1,1,f)) > 0) {
       if (max_byte < read_value) {
           max_byte = read_value;
       }
   }

   printf("%x\n",max_byte);
   
   fclose(f);
   exit(0);
}








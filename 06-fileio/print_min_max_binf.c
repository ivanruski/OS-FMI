// Print min max or all unit16s from bin file

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>

void print_max(char *filename){
   FILE *f = fopen(filename, "r+b");
   int read_size;
   uint16_t read_value;
   uint16_t max = 0;

   while ((read_size = fread(&read_value,2,1,f)) > 0) {
       if (max < read_value) {
           max = read_value;
       }
   }
   fclose(f);
   printf("max: %d\n", max);
}

void print_min(char *filename){
   FILE *f = fopen(filename, "r+b");
   int read_size;
   uint16_t read_value;
   uint16_t min = 65535;

   while ((read_size = fread(&read_value,2,1,f)) > 0) {
       if (min > read_value) {
           min = read_value;
       }
   }
   fclose(f);
   printf("min: %d\n", min);
}


void print_all(char *filename){
   FILE *f = fopen(filename, "r+b");
   int read_size;
   uint16_t read_value;

   while ((read_size = fread(&read_value,2,1,f)) > 0) {
       printf("%d\n",read_value);
   }
   fclose(f);
}

int main(int argc, char* argv[]) 
{
   if (argc != 3 || 
       (strcmp(argv[1],"--min") != 0 && 
       strcmp(argv[1],"--max") != 0 && 
       strcmp(argv[1],"--print") != 0)) {
       
      errx(1,"--<min>|<max>|<print> <path_to_binary_file>\n");
   }

   struct stat f_stat;
   if (stat(argv[2], &f_stat) == -1) {
      err(1, "%s file failed to open\n", argv[2]);
   }

   if (S_ISREG(f_stat.st_mode) == 0) {
      errx(1, "%s file is not a regular file\n", argv[2]);
   }
   
   if (strcmp(argv[1],"--min") == 0) {
      print_min(argv[2]);        
   } 
   
   if (strcmp(argv[1],"--max") == 0) {
      print_max(argv[2]);        
   } 

   if (strcmp(argv[1],"--print") == 0) {
      print_all(argv[2]);        
   } 

   exit(0);
}








// wait command to execute

#include <err.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   if (argc != 2) {
       errx(1,"Provide file name");
   }

   struct stat f;
   if (stat(argv[1], &f) != -1) {    
       if (S_ISDIR(f.st_mode)) {
           errx(1, "%s is directory", argv[1]);
       }
   }

   const int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
   
   int c_pid = fork();
   if (c_pid == 0) {
       char bf1[] = {'f', 'o', 'o' };
       short size1;
       if ((size1 = write(fd,&bf1,sizeof(bf1))) != sizeof(bf1)) {
           err(1, "child write to file unseccessfull\n");
       }
       exit(0);
   }
   //wait(NULL); uncommend if you want foo to be written first
   char bf[] = {'b', 'a', 'r' };
   short size;
   if ((size = write(fd,&bf,sizeof(bf))) != sizeof(bf)) {
       err(1, "child write to file unseccessfull\n");
   }
   
   close(fd);
}

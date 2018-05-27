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
       errx(1,"File name required");
   }

   struct stat f;
   if (stat(argv[1], &f) != -1) {    
       if (S_ISDIR(f.st_mode)) {
           errx(1, "%s is directory", argv[1]);
       }
   }

   int c_pid = fork();

   if (c_pid == 0) {
       const int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
       if (fd == -1) {
           err(1, "%s failed to open", argv[1]);
       }

       char buff[] = {'f','o','o','b','a','r'};
       short write_s;
       if ((write_s = write(fd,&buff,sizeof(buff))) != sizeof(buff)) {
           err(1, "failed writing to %s",argv[1]);
       }
       close(fd);
       exit(0);   
   }

   int status;
   wait(&status);

   if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
       printf("Writing/creating file was unsuccessful");
       exit(1);
   }

   const int fd = open(argv[1],O_RDONLY);
   short read_s;
   char buff[6];
   while ((read_s = read(fd, buff,6)) > 0) {
       for (int i = 0; i < read_s-2; i+=2) {
           write(1, &buff[i],2);
           write(1, " ",1);
       }
       write(1, &buff[read_s -2 ],2);
   }
   write(1,"\n",1);
   close(fd);
   exit(0);



}

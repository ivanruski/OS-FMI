// Copy contetns of one file to another

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        printf("Invalid number of arguments");
        exit(-1);
    }

    int fd1;
    int fd2;

    if ( ( fd1 = open(argv[1], O_RDONLY) ) == -1 ) {
        write(2, "File failed to open in read mode\n",33);
        exit(-1);
    }    

    if ( ( fd2 = open(argv[2],O_CREAT|O_WRONLY, 0777) ) == -1 ) {
        write(2, "File failed to open in write mode", 34);
        close(fd1);
        exit(-1);
    }

    char buffer[4096];
    int readsize;
    while ( ( readsize = read(fd1, &buffer, sizeof(buffer)) ) > 0 ) {
        write(fd2,&buffer,readsize);
    }

    close(fd1);
    close(fd2);
    exit(0);
}

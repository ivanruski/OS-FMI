// Copy etc/passwd and change the delim from : to ?

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() 
{
    int ch_pid = fork();
   
    if (ch_pid == -1) {
        err(1, "Program failed");
    }

    if (ch_pid == 0) { // child process 
      
        if (execl("/bin/cp", "cp", 
                  "/home/ivanruski/../../etc/passwd", 
                  "passwd", 
                  (char *)0) == -1) {
            err(1, "cp failed");
        } 
    }
    
    if (wait(NULL) != -1) {
        if (execl("/bin/sed", "sed", "-i", "-e" "s/:/?/g","passwd", 
            (char *)0) == -1){
            err(1, "wc failed");
        }
    }

    exit(0);
}








#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

struct coordinates {
   uint32_t begin;
   uint32_t end;
};

int get_next_word_cords(int fd,
                        uint32_t lbound,
                        uint32_t file_pos, 
                        struct coordinates *wcoords){
   
   lseek(fd,file_pos,SEEK_SET); 
   char buf;
   
   while (read(fd, &buf,1) > 0 && file_pos >= lbound){
       if (buf == '\0'){
           wcoords->begin = file_pos + 1;
           uint32_t end = file_pos +1;
           while (read(fd, &buf,1) > 0 && buf != '\n'){
               end++;
           }
           wcoords->end = end;
           return 0;
       }
       file_pos--;
       lseek(fd,file_pos,SEEK_SET);
   }

   return -1;
}

int compare_words(int fd, struct coordinates *wcoords, char *match) {
   
   int fsize = wcoords->end - wcoords->begin;
   char found[fsize];
   lseek(fd,wcoords->begin, SEEK_SET);
   
   if (read(fd,&found,fsize) != fsize){
       return -1;
   }
  
   int msize = strlen(match);  
   int limit = msize > fsize ? fsize : msize;
   for (int i = 0; i< limit; i++) {
       if (match[i] == found[i]){
           continue;
       }
       else if (match[i] > found[i]) {
           return 1;
       }
       else{
           return -1;
       }
   }
   
   if (msize > fsize)
       return 1;
   else if (fsize > msize)
       return -1;
   else
      return 0;
}

int find_word(int fd,
              uint32_t l,
              uint32_t r,
              struct coordinates *wcoords, 
              char *match) {
   
   if (l > r) 
       return -1;

   uint32_t file_pos = (r+ l) / 2;  
   if (get_next_word_cords(fd, l, file_pos, wcoords) == -1) {
      // if "l" boundary is encountered 
      // run for the right subset
      return find_word(fd, file_pos+1, r, wcoords, match);
   }
   
   int result = compare_words(fd, wcoords,match);
   if (result == 0) {
       return 0;
   }
   else if(result == 1) {
      return find_word(fd,file_pos + 1, r, wcoords, match); 
   }
   else {
      return find_word(fd,l, file_pos - 1, wcoords, match);
   }
}

void print_description(int fd, uint32_t seek_pos) {
   lseek(fd, seek_pos,SEEK_SET);
   
   char buf;
   while(read(fd, &buf,1) > 0 && buf != '\0'){
       write(1,&buf,1);
   }
}

int main (int argc, char *argv[]) {

   if (argc != 3) {
      errx(1,"Usage: <dictionary-to-search-from> <word-to-find>");
   }
   
   struct stat st;
   if(stat(argv[1], &st) == -1) {
      err(1,"could't get the size of %s",argv[1]);   
   }

   uint64_t file_size = st.st_size;
   const int fd = open(argv[1], O_RDONLY);
   struct coordinates wcoords;

   int status = find_word(fd, 0, file_size, &wcoords, argv[2]);
   if (status == 0) {
       print_description(fd, wcoords.end+1);
   }
   else {
       write(1, "Word was not found\n",20);
   }
   
   close(fd);
   exit(0);
}

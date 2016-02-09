#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(){
  int fd =  open("test.txt", O_WRONLY | O_CREAT, S_IRWXU);
  fprintf(stderr, "fd=%d\n", fd);
  fprintf(stderr, "STDOUT_FILENO=%d\n", STDOUT_FILENO);
  fprintf(stderr, "STDIN_FILENO=%d\n", STDIN_FILENO);
  dup2 (fd, STDOUT_FILENO);
  printf("hello world!");
}
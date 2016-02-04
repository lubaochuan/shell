#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(){
  int fd =  open("test.txt", O_WRONLY | O_CREAT);
  dup2 (fd, STDOUT_FILENO);
  printf("hello world!");
}
/* modified from fork.c in Advanced Linux Programming (page 49) */
/* http://www.makelinux.net/alp/024 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  pid_t child_pid;

  printf("the main program process ID is %d\n", (int) getpid());

  child_pid = fork();
  if(child_pid != 0){
    printf("this is the parent process, with id %d\n", (int)getpid());
    printf("child_pid=%d\n", child_pid);
  }else{
    printf("this is the child  process, with id %d\n", (int)getpid());
    printf("child_pid=%d\n", child_pid);
  }
}

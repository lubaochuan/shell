/* from Advanced Linux Programming (page 113) */
/* http://www.makelinux.net/alp/038 */
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 

int main () {
  int fds[2]; 
  pid_t pid; 

  /* Create a pipe. File descriptors for the two ends of the pipe are 
     placed in fds.  */ 
  pipe (fds); 

  printf("fds[0]=%d, fds[1]=%d\n", fds[0], fds[1]);

  /* Fork a child process.  */ 
  pid = fork (); 

  if (pid == (pid_t) 0) {
    /* This is the child process. Close our copy of the write end of 
       the file descriptor.  */ 
    close (fds[1]); 

    /* Connect the read end of the pipe to standard input.  */ 
    dup2 (fds[0], STDIN_FILENO); 

    /* Replace the child process with the "sort" program.  */ 
    execlp ("sort", "sort", NULL); 
  } else {
    /* This is the parent process.  */ 
    FILE* stream; 

    /* Close our copy of the read end of the file descriptor.  */ 
    close (fds[0]); 

    /* Connect the write end of the pipe to standard out, and write 
       to it.  */ 
    dup2(fds[1], STDOUT_FILENO);
    printf ("This is a test.\n"); 
    printf ("Hello, world.\n"); 
    printf ("My dog has fleas.\n"); 
    printf ("This program is great.\n"); 
    printf ("One fish, two fish.\n"); 
    fflush(stdout);
    close(fds[1]);
    close(STDOUT_FILENO);

    /* Wait for the child process to finish.  */ 
    waitpid (pid, NULL, 0); 
    printf("parent process terminated.\n");
  } 
  return 0; 
} 

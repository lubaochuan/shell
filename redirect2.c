#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <fcntl.h>

int main () {
  /*  The argument list to pass to the "ls" command.  */ 
  char* arg_list[] = {
    "ls",     /* argv[0], the name of the program.  */ 
    "-l", 
    "/", 
    NULL      /* The argument list must end with a NULL.  */ 
  }; 

  /* Spawn a child process running the "ls" command. */
  pid_t child_pid = fork (); 

  if (child_pid == 0){
    /* This is the child process. */ 
    char * filename = "test.txt";
    int outfile = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
    if (outfile == -1){
      fprintf(stderr, "Error: failed to create file %s\n", filename);
    }else{
      /* redirect the standard output from this process to the file. */
      if(dup2(outfile, STDOUT_FILENO) != STDOUT_FILENO){
        fprintf(stderr, "Error: failed to redirect standard output\n");
      }

      /* Now execute PROGRAM, searching for it in the path.  */ 
      execvp (arg_list[0],  arg_list); 
      /* The execvp  function returns only if an error occurs.  */ 
      fprintf (stderr,  "an error occurred in execvp\n"); 
      abort (); 
    }
  }
  /* only the parent process executes the following code. */
  fprintf(stdout, "Hello from the parent process.\n");

  /* Wait for the child process to complete.  */ 
  int child_status;
  waitpid (child_pid, &child_status, 0); 
  
  if (WIFEXITED (child_status)){
    printf ("the child process exited normally, with exit code %d\n", 
	     WEXITSTATUS (child_status)); 
  }else{ 
    printf ("the child process exited abnormally\n"); 
  }
  
  return  0; 
} 

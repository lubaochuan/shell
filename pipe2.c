#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int run_command(char** arg_list, int rd, int wd) {
  pid_t child_pid;

  /* Duplicate this process. */
  child_pid = fork();

  if (child_pid != 0){
    /* This is the parent process. */
    return child_pid;
  }else {
    if (rd != STDIN_FILENO){
      if(dup2(rd, STDIN_FILENO) != STDIN_FILENO){
        fprintf(stderr, "Error: failed to redirect standard input\n");
        return -1;
      }
    }

    if (wd != STDOUT_FILENO){
      printf("redirect stdout to %d.", wd);
      if(dup2(wd, STDOUT_FILENO) != STDOUT_FILENO){
        fprintf(stderr, "Error: failed to redirect standard output\n");
        return -1;
      }
    }
    /* Now execute PROGRAM, searching for it in the path.  */
    execvp (arg_list[0], arg_list);
    /* The execvp  function returns only if an error occurs.  */
    fprintf(stderr,  "an error occurred in execvp\n");
    abort();
  }
}

int main () {
  /*  The argument list to pass to the "ls" command.  */
  char* arg_list[] = {
    "ls",     /* argv[0], the name of the program.  */
    "-l",
    "|",      /* the pipe symbol is at index 2 */
    "wc",
    "-l",
    NULL      /* The argument list must end with a NULL.  */
  };

  int pipe_index = 2;
  int rd = STDIN_FILENO;
  int wd = STDOUT_FILENO;
  int fds[2];
  if (pipe(fds) != 0) {
    fprintf(stderr, "Error: unable to pipe command '%s'\n", arg_list[0]);
    return -1;
  }

  wd = fds[1]; /*file descriptor for the write end of the pipe*/

  // delete the pipe symbol and insert a null to terminate the
  // first command's argument list
  arg_list[pipe_index] = NULL;

  // run first command: read from STDIN and write to the pipe
  run_command(arg_list, rd, wd);
  close(fds[1]);

  rd = fds[0];
  wd = STDOUT_FILENO;

  // run the second command: read from the pipe and write to STDOUT
  // the argument for this command starts at pipe_index+1
  run_command(arg_list+pipe_index+1, rd, wd);

  fprintf (stderr, "done with main program\n");
  return 0;
}

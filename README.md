# Unix/Linux Shell
Examples from [Advanced Unix Programing with Linux](http://www.makelinux.net/alp/)

## Chapter 3. Processes

A process is a running instance of a program. The Unix shell is process, which
can be used to create and contral other processes. We can use multiple
cooperating processes in the same application. Most process manipulation
functions are found in `<unistd.h>`.

`print-pid.c` uses `getpid()` and `getppid()` system calls to get process IDs.

`ps -o pid,user,start_time,command` displays the process ID, the name of the
user owning the process, the wall clock time at which the process started, and
the command running in the process.

New processes can be created in two ways:
* `system` function (less flexible and may introduce security risks)
* `fork` and `exec` method

`fork.c` creates a new process by duplicating/cloning the current process.

`fork-exec.c` uses `exec` functions to replace the child process image with
another program.

Signals are mechanisms for communicating with and manipulating processes in
Linux. `sigusr1.c` counts the number of `SIGUSR1` signals received
([on sending signals to processes](https://bash.cyberciti.biz/guide/Sending_signal_to_Processes)).

`make-zombie.c` shows that if a child process terminates and the parent process
is not there to receive the termination status code (didn't call `wait`) the
child process becomes a zombie process. Run this program and issue the following
command a few times:
```
ps -e -o pid,ppid,stat,cmd
```

`sigchild.c` cleans up child process by handling `SIGCHLD` signal.

## Chapter 5. Interprocess Communication

`shm.c` shows interprocess communication via shared memory. Use `ipcs -m` to
see the shared memory segment.

`pipe.c` and `pipe2.c` demonstrate communication with a child process using a pipe.

`redirect.c` and `redirect2.c` shows IO redirection via the `dup2` system call
([see dup2 man page](http://man7.org/linux/man-pages/man2/dup.2.html)).

`popen.c` demonstrates the `popen` and the `pclose` functions.

A _first-in, first-out (FIFO)_ file is a nameed pipe in the filesystem.
```
$ mkfifo /tmp/fifo
$ ls -l /tmp/fifo
prw-r--r-- 1 ubuntu ubuntu 0 Feb 20 12:45 /tmp/fifo|
```
Run `cat < /tmp/fifo` in one terminal and run `cat > /tmp/fifo`. What you type
in the second termial will get "piped" to the first termial. To close the pipe
press Ctrl+D in the second terminal.

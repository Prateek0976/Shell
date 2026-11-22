# Writing a Prototype of a shell in C
## myshell
myshell is a small unix style shell written in C. It was done to learn more about how commands like fork(), execvp() and other system functions like built-ins, IPC and more work.

## How to Build and Run
1. Clone the repository:
   `git clone https://github.com/Prateek0976/Shell.git`
2. Compile the code:
   `make`
3. Run the shell:
   `./myshell`

## What has been done
myshell has following functions:
- supports common system commands like ls, mkdir and such
- supports built-ins like cd, pwd, exit
- supports redirection of commands
- supports pipelining of commands
- supports control signal for Ctrl + c
- Valgrind test for memory leaks

## Limitations in myshell
Limitations in myshell are:
- Limited number of built-ins
- There must be space between each command as custom function written to separate commands works around separating them by space
- Control signal currently supported is only Ctrl + c
- Empty at beginning or end of piping command makes it stuck
- There is limit of hundred characters as input due to lack of use of dynamic memory allocation

## What I learned doing this Project
- Basics of C language
- How a unix style shell works
- About InterProcess communication in system
- How system commands like fork(), execvp(), getcwd() and more work

## Future Improvements
- Adding more control signals
- Removing limitation of space in between each command
- Using Dynamic memory allocation to remove limit of hundred characters in input command
- Adding more built-ins

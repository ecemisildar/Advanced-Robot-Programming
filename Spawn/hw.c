// analyze this code in details:
//A - what is expected to do as it is?
//B - what is expected to do when removing the "//" comments?
//C - are you able to use this method to execute "first"and "second" codes inside the previous exercise? Hint: use fork() to generate two processes, and let the two processes to execute sepratly two different executables

// In this code parent process ask two numbers and child calculates the mean and sum of these numbers
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(const char * program, char ** arg_list) {
  pid_t child_pid = fork();
  if (child_pid != 0)
    return child_pid;
  else {
    execvp (program, arg_list);
    perror("exec failed");
    return 1;
 }
}

int main() {
  char * arg_list_1[] = { "/home/ecem/Documents/arp_codes/3-oct/first", NULL };
  char * arg_list_2[] = { "/home/ecem/Documents/arp_codes/3-oct/second", NULL };
  spawn("/home/ecem/Documents/arp_codes/3-oct/second", arg_list_2); // executes the child process
  spawn("/home/ecem/Documents/arp_codes/3-oct/first", arg_list_1); // executes the parent processor
  
  
  printf ("Main program exiting...\n");
  
  return 0;
}


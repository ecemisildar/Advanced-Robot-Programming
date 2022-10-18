#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(const char * program, char * arg_list[]) {
pid_t child_pid = fork();
if (child_pid != 0)
return child_pid;
    else {
    if (execvp (program, arg_list) == 0);
    perror("exec failed");
    return 1;
    }
}

int main() {
  char * arg_list_1[] = { "/usr/bin/konsole", "-e", "/home/ecem/Documents/arp_codes/3-oct/first", (char*)NULL };
  char * arg_list_2[] = { "/usr/bin/konsole", "-e", "/home/ecem/Documents/arp_codes/3-oct/second", (char*)NULL };
  pid_t pid_1 = spawn("/usr/bin/konsole", arg_list_1);
  pid_t pid_2 = spawn("/usr/bin/konsole", arg_list_2);
  
  int status;
  wait(&status);
  
  printf ("Main program exiting with status %d\n", status);
  return 0;
}


#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t this_pid;

  this_pid = getpid();
  printf("This process's PID is %d\n", this_pid);

  sleep(100);
  return EXIT_SUCCESS;
}

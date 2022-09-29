#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t child_pid;
  child_pid = fork();

  for (pid_t i = 0; i < 4; i++) {
    switch (child_pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0:
      printf("I am the child process with PID %d\n", getpid());
      child_pid = fork();
      sleep(1);
      break;
    case 1:
      printf("I am the parent process with PID %d\n", getpid());
      break;
    }
  }

  return 0;
}

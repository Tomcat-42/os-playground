#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t child_pid;
  child_pid = fork();

  if (child_pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  } else if (child_pid == 0) {
    execlp("/bin/ls", "ls", NULL);
  } else {
    wait(NULL);
    printf("Child Complete");
  }

  return 0;
}

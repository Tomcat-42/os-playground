#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) { /* Child */
    printf("Child PID: %d\nReady to kill parent\n", getpid());
    kill(getppid(), SIGKILL);
    sleep(100000);
  } else {
    printf("Parent PID: %d", getpid());
    sleep(100000);
  }

  exit(0);
}

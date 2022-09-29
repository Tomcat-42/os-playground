#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 4

/* This code creates a visual representation
 * of a process tree. The tree is created by
 * forking the parent process N times. Each
 * child process forks itself N times. The
 * tree is printed to the terminal using
 * printf statements.
 * */
int main(void) {
  pid_t parent_pid, child_pid, current_pid;

  // print the root node
  printf("Level 0: %d\n", getpid());

  for (pid_t i = 0; i < N; i++) {
    child_pid = fork();

    switch (child_pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0: // child process
      current_pid = getpid();
      printf("%d\n", child_pid);
      child_pid = fork();
      break;
    default:      // parent process
      wait(NULL); // wait for all children to finish
      // print the parent node
      printf("%*s%d\n", 2 * (i + 1), "=", getpid());
      break;
    }
  }

  return 0;
}

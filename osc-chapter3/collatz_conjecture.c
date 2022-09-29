#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



/* The collatz conjecture is a conjecture in mathematics that concerns a
 * sequence defined as follows: n = n/2 (n is even), n = 3n + 1 (n is odd)
 *
 * The objective of this program is to recive a number n from the user and
 * fork a process that will calculate the collatz conjecture for n and print
 * the result to the screen.
 */
int main(int argc, char *argv[]) {
  int n;
  int pid;
  int status;

  if (argc != 2) {
    printf("Usage: %s <n>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);

  if (n <= 0) {
    fprintf(stderr, "Error: n must be a positive integer\n");
  }

  pid = fork();

  switch (pid) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
    break;
  case 0: // child
    while (n != 1) {
      printf("%d ", n);
      if (n % 2 == 0) {
        n /= 2;
      } else {
        n = 3 * n + 1;
      }
    }
    printf("%d\n", n);

  default:         // parent
    wait(&status); // wait for sync
    break;
  }
}

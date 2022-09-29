#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fcntl.h>

#define NAME "collatz_shm"
#define BUF_SIZE 1024

/* The collatz conjecture is a conjecture in mathematics that concerns a
 * sequence defined as follows: n = n/2 (n is even), n = 3n + 1 (n is odd)
 *
 * The objective of this program is to recive a number n from the user and
 * fork a process that will calculate the collatz conjecture for n and save the
 * result to a shared memory segment. After the child process has finished, the
 * parent process will print the result to the screen.
 *
 * This version uses shared memory to communicate between the parent and
 * child processes.
 */
int main(int argc, char *argv[]) {
  int n;
  int pid;
  int status;
  int shm_id;
  int *shm_ptr;

  if (argc != 2) {
    printf("Usage: %s <n>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((n = atoi(argv[1])) <= 0) {
    fprintf(stderr, "Error: n must be a positive integer\n");
  }

  /* Initializes the shared memory segment */
  if ((shm_id = shm_open(NAME, O_CREAT | O_RDWR, 0666)) == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }
  ftruncate(shm_id, sizeof(int) * BUF_SIZE);
  if (!(shm_ptr = mmap(0, sizeof(int) * BUF_SIZE, PROT_READ | PROT_WRITE,
                       MAP_SHARED, shm_id, 0))) {
    perror("mmap");
    exit(EXIT_FAILURE);
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

#include <fcntl.h>
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

#define MAX_CMD_LEN 1024
#define NAME "time_shm"

int main(int argc, char *argv[]) {
  pid_t pid;
  id_t shm_id;   // shared memory id
  char *shm_ptr; // shared memory pointer
  struct timeval end, *start;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <command> <...command args>", argv[0]);
    exit(1);
  }

  /* Creation and mapping of the shm object*/
  shm_id = shm_open(NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_id, sizeof(struct timeval));
  shm_ptr = mmap(0, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED,
                 shm_id, 0);

  /* Creation of the child process */
  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    /* Child process */
    gettimeofday((struct timeval *)shm_ptr, NULL);
    execvp(*(argv + 1), argv + 1);
  } else { /* Parent process */
    wait(NULL);
    gettimeofday(&end, NULL);
    start = (struct timeval *)shm_ptr;

    printf("\nElapsed time: %ldms\n",
           ((end.tv_sec - start->tv_sec) * 1000000L + end.tv_usec) -
               start->tv_usec);
  }

  exit(0);
}

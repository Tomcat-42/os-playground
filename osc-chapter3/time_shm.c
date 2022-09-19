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

enum { READ, WRITE } pipe_ends;

int main(int argc, char *argv[]) {
  pid_t pid;
  /* File descriptors of the pipe, read and write ends */
  int fd[2];
  struct timeval end, *start;

  /* Memory buffer */
  void *buffer = (void *)malloc(sizeof(struct timeval));

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <command> <...command args>", argv[0]);
    exit(1);
  }

  /* create the pipe */
  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    free(buffer);
    return 1;
  }

  /* Creation of the child process */
  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    /* Child process */
    close(fd[READ]);                                  // close unused pipe end
    gettimeofday((struct timeval *)buffer, NULL);     // get time to buffer
    write(fd[WRITE], buffer, sizeof(struct timeval)); // write to pipe
    execvp(*(argv + 1), argv + 1);
  } else {                                          /* Parent process */
    close(fd[WRITE]);                               // close unused pipe end
    wait(NULL);                                     // wait for child to finish
    gettimeofday(&end, NULL);                       // get end time
    read(fd[READ], buffer, sizeof(struct timeval)); // read from pipe
    start = (struct timeval *)buffer;

    printf("\nElapsed time: %ldms\n",
           ((end.tv_sec - start->tv_sec) * 1000000L + end.tv_usec) -
               start->tv_usec);
  }

  // cleanup
  free(buffer);
  close(fd[READ]);
  close(fd[WRITE]);

  exit(0);
}

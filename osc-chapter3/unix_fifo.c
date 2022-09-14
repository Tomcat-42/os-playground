#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "MYFIFO.fifo"
#define FIFO_MSG "Hello, World!"
#define BUFFER_SIZE 20

int main(void) {
  int fifo_fd;
  int child_pid;
  int msg_len = strlen(FIFO_MSG);
  char buffer[msg_len + 1];

  mkfifo(FIFO_FILE, 0666);

  child_pid = fork();

  if (child_pid < 0) {
    fprintf(stderr, "fork() failed");
    exit(1);
  }

  if (child_pid == 0) { // child process
    fifo_fd = open(FIFO_FILE, O_RDONLY);
    read(fifo_fd, &buffer, msg_len);
    printf("Child => Reading '%s' from FIFO\n", buffer);
  } else { // parent
    printf("Parent => Writing '" FIFO_MSG "' to FIFO\n");
    fifo_fd = open(FIFO_FILE, O_WRONLY);
    write(fifo_fd, FIFO_MSG, msg_len);
  }
}

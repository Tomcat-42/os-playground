// Userspace copying example

#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096 * 1000

void usage(char *progname) {
  printf("Usage: %s <file1> <file2>\n", progname);
  exit(0);
}

void kill(char *msg) {
  printf("Error: %s\n", msg);
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    usage(argv[0]);

  char buffer[BUFSIZE];
  int fd0, fd1, n;
  struct stat status_buffer;

  // use raw syscalls to open the files
  fd0 = open(argv[1], O_RDONLY);
  fstat(fd0, &status_buffer); // copy the file permissions
  if (fd0 < 0)
    kill("Error opening file1");
  fd1 = open(argv[2], O_WRONLY | O_CREAT, status_buffer.st_mode);
  if (fd1 < 0)
    kill("Error opening file2");

  // copying using a buffer (on userspace)
  while ((n = read(fd0, &buffer, BUFSIZE)) > 0) {
    if (write(fd1, buffer, n) != n)
      kill("Error writing to file2");
  }

  return 0;
}

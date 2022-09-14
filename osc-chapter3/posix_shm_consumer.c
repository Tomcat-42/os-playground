#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  const int SIZE = 4096;
  const char *name = "OS";

  int shm_fd;
  char *ptr;

  // open the shared memory segment
  shm_fd = shm_open(name, O_RDONLY, 0666);

  // mmap the shared memory segment
  ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  // read from the shared memory segment
  printf("%s", (char *)ptr);

  // remove the shared memory segment
  shm_unlink(name);

  return 0;
}

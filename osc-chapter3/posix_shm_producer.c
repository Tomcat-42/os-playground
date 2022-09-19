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

  const char *msg0 = "Hello World";
  const char *msg1 = "Hello World1";

  int shm_fd;
  char *ptr;

  // create the shared mem file object
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  // configure the size of the shared mem object
  ftruncate(shm_fd, SIZE);

  // memory map the shared mem object
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  // write to the shared mem object
  sprintf(ptr, "%s", msg0);
  ptr += strlen(msg0);
  sprintf(ptr, "%s", msg1);
  ptr += strlen(msg1);

  return 0;
}

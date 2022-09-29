#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t this_ppid;

  this_ppid = getppid();
  printf("This process's PPID is %d\n", this_ppid);

  sleep(100);
  return EXIT_SUCCESS;
}

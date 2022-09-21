#include "main.h"
#include "pid_manager/pid_manager.h"
#include <stdio.h>

#define SIZE 1000
#define MIN 300
#define MAX 350

int main() {
  pid_manager *manager;
  pid_t pid;

  if (!(manager = pid_manager_new(SIZE, MIN, MAX))) {
    printf("Failed to create pid manager\n");
    return 1;
  }

  for (int i = 0; i <= 70; i++) {
    pid = pid_manager_allocate(manager);
    // printf("Allocated pid: %d\n", pid);
  }

  pid_manager_release(manager, 300);

  pid = pid_manager_allocate(manager);

  printf("Allocated pid: %d\n", pid);

  pid_manager_release(manager, 340);

  pid = pid_manager_allocate(manager);

  printf("Allocated pid: %d\n", pid);

  pid_manager_delete(manager);

  return 0;
}

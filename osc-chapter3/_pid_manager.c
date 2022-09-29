#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define MIN_PID 300
#define MAX_PID 5000
#define MAX_SIZE 6000

/**
 * @brief The pid_map array is used to represent pids.
 * A value of 0 at index i indicates that the pid i is available.
 * A value of 1 at index i indicates that the pid i is in use.
 *
 * @field uint8_t available : 1 0 if pid is available, 1 if pid is in use
 */
struct pid_map {
  uint8_t available : 1; // 0 = available, 1 = not available
};

/**
 * @brief Allocate and initialize a data structure for representing pids;
 * @field pid_map *map - pointer to the pid_map struct
 * @field int size - size of the pid_map struct
 * @field int min_pid - minimum pid value
 * @field int max_pid - maximum pid value
 * @field int next_pid - next pid value
 * @field int last_pid - last pid value
 */
// struct pid_manager {
//   struct pid_map *map; // status map
//   pid_t size;          // number of differents pids
//
//   pid_t min; // minimum pid
//   pid_t max; // maximum pid
//
//   pid_t last;    // last pid deallocated
//   pid_t current; // current pid to allocate
// };
/**
 * @brief Allocate and initialize a data structure for representing pids;
 * @field pid_map *map - pointer to the pid_map struct
 * @field int size - size of the pid_map struct
 * @field int min_pid - minimum pid value
 * @field int max_pid - maximum pid value
 * @field int next_pid - next pid value
 * @field int last_pid - last pid value
 */
struct pid_manager {
  struct pid_map *map; // status map
  pid_t size;          // number of differents pids

  pid_t min; // minimum pid
  pid_t max; // maximum pid

  pid_t last;    // last pid deallocated
  pid_t current; // current pid to allocate
};

/* @brief initialize the pid manager
 * @param size number of differents pids (MUST be >= max)
 * @param min minimum pid range
 * @param max maximum pid range
 * @return 0 if success, -1 otherwise
 *
 * eg, pid_manager_init(10, 3, 9):
 *
 * <reserved><--------available--------><reserved>
 *  ----------------------------------------
 * | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
 *  ----------------------------------------
 *
 */
struct pid_manager *pid_manager_new(ssize_t size, ssize_t min, ssize_t max) {
  struct pid_manager *manager =
      (struct pid_manager *)malloc(sizeof(struct pid_manager));

  if (manager == NULL) {
    return NULL;
  }

  manager->size = size;

  manager->min = min;
  manager->max = max;

  manager->last = -1;
  manager->current = min;

  manager->map = calloc(manager->size, sizeof(struct pid_map));

  if (manager->map == NULL) {
    free(manager);
    return NULL;
  }

  return manager;
}

/* @brief allocate and return a pid
 * @return pid if success, -1 otherwise
 */
pid_t pid_manager_allocate(struct pid_manager *pid_manager) {
  if (pid_manager == NULL) {
    return -1;
  }

  /* Number of iterations */
  pid_t traversals = 0;

  /* normal linear search */
  for (pid_t i = pid_manager->current; traversals < pid_manager->size;
       i = ((i + 1) % pid_manager->max + pid_manager->min)) {
    /* found a free pid */
    if (!pid_manager->map[i].available) {
      pid_manager->map[i].available = 1;
      pid_manager->current = i + 1;
      return i;
    }
  }

  return -1;
}

/* @brief release a pid
 * @param pid pid to release
 * @return void
 */
void pid_manager_release(struct pid_manager *pid_manager, pid_t pid) {
  if (pid_manager == NULL) {
    return;
  }

  if (pid < pid_manager->min || pid > pid_manager->max) {
    return;
  }

  pid_manager->map[pid].available = 0;
  pid_manager->last = pid;
}

/**
 * @brief free the pid manager
 * @param pid_manager the pid manager to free
 */
void pid_manager_free(struct pid_manager *pid_manager) {
  if (pid_manager == NULL) {
    return;
  }

  free(pid_manager->map);
  free(pid_manager);
}

int main() {
  struct pid_manager *manager = pid_manager_new(10, 3, 7);
  pid_t pid;

  if (manager == NULL) {
    return -1;
  }

  printf("size of the pid_map: %zu\n", sizeof(*manager->map));

  // for (int i = 0; i < MAX_SIZE; i++) {
  //   pid = pid_manager_allocate(manager);
  //   printf("Allocated pid: %d\n", pid);
  // }

  return 0;
}

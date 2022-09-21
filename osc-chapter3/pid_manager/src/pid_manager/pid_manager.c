#include "pid_manager/pid_manager.h"
#include "bitmap/bitmap.h"

#include <assert.h>

pid_manager *pid_manager_new(pid_t size, pid_t min, pid_t max) {
  assert(size > 0);
  assert(min > 0);
  assert(max > 0);
  assert(min < max);
  assert(size >= max);

  pid_manager *manager;

  if (!(manager = calloc(1, sizeof(pid_manager)))) {
    return NULL;
  }

  if (!(manager->pid_status = bitmap_new(size))) {
    free(manager);
    return NULL;
  }

  manager->size = size;
  manager->allocable_size = max - min + 1;

  manager->min_pid = min;
  manager->max_pid = max;

  manager->last_released_pid = -1;
  manager->current_pid = min;

  return manager;
}

/* @brief allocate and return a pid
 * @return pid if success, -1 otherwise
 */
pid_t pid_manager_allocate(pid_manager *pid_manager) {
  assert(pid_manager != NULL);

  /* Number of iterations */
  pid_t traversals = 0;

  /* normal linear search */
  for (pid_t i = pid_manager->current_pid;
       traversals < pid_manager->allocable_size;
       i = ((((i - pid_manager->min_pid) + 1) % pid_manager->allocable_size) +
            pid_manager->min_pid),
             traversals++) {
    /* found a free pid */
    if (!bitmap_get(pid_manager->pid_status, i)) {
      bitmap_set(pid_manager->pid_status, i);
      pid_manager->current_pid = i;
      return i;
    }
  }

  return -1;
}

/* @brief release a pid
 * @param pid pid to release
 * @return void
 */
void pid_manager_release(pid_manager *pid_manager, pid_t pid) {
  assert(pid_manager != NULL);
  assert(pid >= pid_manager->min_pid);
  assert(pid <= pid_manager->max_pid);

  bitmap_clear(pid_manager->pid_status, pid);
  pid_manager->last_released_pid = pid;
}

void pid_manager_delete(pid_manager *manager) {
  assert(manager != NULL);

  bitmap_delete(manager->pid_status);
  free(manager);
}

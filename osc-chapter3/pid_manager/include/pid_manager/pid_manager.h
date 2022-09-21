#pragma once

#include <bitmap/bitmap.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * @brief Allocate and initialize a data structure for representing pids;
 * @field bitmap *pid_status - pointer to the pids bitmap
 * @field int size - possible number of different pids (MUST be at least
 * max_pid)
 * @field int min_pid - minimum pid value
 * @field int max_pid - maximum pid value
 * @field int next_pid - next pid value
 * @field int last_pid - last pid value
 */
typedef struct pid_manager {
  bitmap *pid_status; // status map

  pid_t size;           // number of differents pids
  pid_t allocable_size; // number of allocable pids

  pid_t min_pid; // minimum pid
  pid_t max_pid; // maximum pid

  pid_t last_released_pid; // last pid released
  pid_t current_pid;       // current pid to allocate
} pid_manager;

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
 */
pid_manager *pid_manager_new(pid_t size, pid_t min, pid_t max);

/* @brief allocate and return a pid
 * @return pid if success, -1 otherwise
 */
pid_t pid_manager_allocate(pid_manager *pid_manager);

/* @brief release a pid
 * @param pid pid to release
 * @return void
 */
void pid_manager_release(pid_manager *pid_manager, pid_t pid);

/**
 * @brief free the pid manager
 * @param pid_manager the pid manager to free
 */
void pid_manager_delete(pid_manager *pid_manager);

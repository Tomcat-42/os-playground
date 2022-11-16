/* A simple c program that linearly searches an array of integers on 2 different
 * threads */
#include <linux/unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct linear_search_args {
  int *array;
  int size;
  int value;
};

int linear_search(struct linear_search_args *args) {
  int tid = syscall(SYS_gettid);

  int i;
  for (i = 0; i < args->size; i++) {
    if (args->array[i] == args->value) {
      printf("Found value %d at index %d in thread %d\n", args->value, i, tid);
      return i;
    }
  }
  return -1;
}

int main() {
  int i;
  struct linear_search_args args1;

  args1.size = 1000000;
  args1.array = malloc(sizeof(int) * args1.size);
  args1.value = 100;

  pthread_t p1, p2;

  srand(time(NULL));
  for (i = 0; i < args1.size; i++) {
    args1.array[i] = rand() % 1000;
  }
  p1 = pthread_create(&p1, NULL, &linear_search, &args1);
  p2 = pthread_create(&p2, NULL, &linear_search, &args1);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
}

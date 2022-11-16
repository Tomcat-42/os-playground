#include <linux/unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function() {
  int tid;
  int i;
  tid = syscall(SYS_gettid);

  pthread_mutex_lock(&mutex);

  for (i = 0; i < 20; i++) {
    printf(" thread pid %d %d\n", tid, i);
    usleep(10);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main() {
  pthread_t p1, p2;

  pthread_create(&p1, NULL, &thread_function, NULL);
  pthread_create(&p2, NULL, &thread_function, NULL);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  return 0;
}

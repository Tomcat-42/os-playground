#include <linux/unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

void *thread_function() {
  int i;
  int tid;
  tid = syscall(SYS_gettid);
  for (i = 0; i < 20; i++) {
    printf(" thread pid %d %d\n", tid, i);
    usleep(10);
  }
  return NULL;
}

int main() {
  pthread_t p1, p2;
  int tid = syscall(SYS_gettid);

  printf("MAIN: thread pid %d\n", tid);

  pthread_create(&p1, NULL, &thread_function, NULL);
  pthread_create(&p2, NULL, &thread_function, NULL);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  return 0;
}

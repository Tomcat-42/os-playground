#include <linux/unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

volatile int i;

void *thread_function() {
  int tid, pid;
  tid = syscall(SYS_gettid);
  pid = syscall(SYS_getpid);

  for (; i < 100; i++) {
    printf(" thread tid -> %d; pid->  %d\n", tid, pid);
    usleep(10);
  }
  return NULL;
}

int main() {
  pthread_t p1, p2;
  int pid = syscall(SYS_getpid);
  int tid = syscall(SYS_gettid);

  i = 0;

  // printf("i = %d\n", i);
  // printf("main pid -> %d; tid -> %d\n", pid, tid);

  pthread_create(&p1, NULL, &thread_function, NULL);
  pthread_create(&p2, NULL, &thread_function, NULL);

  // pthread_join(p1, NULL);
  // pthread_join(p2, NULL);
  return 0;
}

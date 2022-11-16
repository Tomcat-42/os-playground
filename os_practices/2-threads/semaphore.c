#include <linux/unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

sem_t semid;

void *thread_function() {
  int tid;
  int i;
  tid = syscall(SYS_gettid);
  sem_wait(&semid);
  for (i = 0; i < 20; i++) {
    printf(" thread pid %d %d\n", tid, i);
    usleep(10);
  }
  sem_post(&semid);
  return NULL;
}

int main() {
  pthread_t p1, p2;
  sem_init(&semid, 0, 1);
  pthread_create(&p1, NULL, &thread_function, NULL);
  pthread_create(&p2, NULL, &thread_function, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  sem_destroy(&semid);
  return 0;
}

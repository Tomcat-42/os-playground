#include <linux/unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

// volatile int i;

// define a semaphore
sem_t sem;

void *thread_function0() {
  int tid, pid;
  tid = syscall(SYS_gettid);
  pid = syscall(SYS_getpid);

  sem_wait(&sem);
  for (int i = 0; i < 20; i++) {
    printf(" thread0 tid -> %d; pid->  %d\n", tid, pid);
    usleep(10);
  }
  sem_post(&sem);

  return NULL;
}

void *thread_function1() {
  int tid, pid;
  tid = syscall(SYS_gettid);
  pid = syscall(SYS_getpid);

  for (int i = 0; i < 100; i++) {
    printf(" thread1 tid -> %d; pid->  %d\n", tid, pid);
    usleep(10);
  }

  return NULL;
}

int main() {
  pthread_t p1, p2;
  // int pid = syscall(SYS_getpid);
  // int tid = syscall(SYS_gettid);

  // int i = 0;

  // initialize semaphore
  sem_init(&sem, 0, 1);

  pthread_create(&p1, NULL, &thread_function0, NULL);
  // pthread_create(&p2, NULL, &thread_function1, NULL);
  pthread_create(&p2, NULL, &thread_function0, NULL);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  return 0;
}

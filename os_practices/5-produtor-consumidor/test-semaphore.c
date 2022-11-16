#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

#define N 5

int buffer[N];
volatile int count = 0;

// define a semaphore
sem_t sem;

// define a mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer() {
  int in = 0;
  for (int i = 0; i < 10000; i++) {
    while (count == N)
      ;

    buffer[in] = i;
    in = (in + 1) % N;
    // printf("producer: %d\n", i);

    sem_wait(&sem);
    count++;
    sem_post(&sem);
  }

  return NULL;
}

void *consumer() {
  int out = 0;
  int d_out;

  for (int i = 0; i < 10000; i++) {
    while (count == 0)
      ;

    d_out = buffer[out];
    out = (out + 1) % N;
    // printf("consumer: %d\n", d_out);

    sem_wait(&sem);
    count--;
    sem_post(&sem);
  }

  return NULL;
}

int main() {
  pthread_t t1, t2;

  // initialize semaphore
  sem_init(&sem, 0, 1);

  pthread_create(&t1, NULL, &producer, NULL);
  pthread_create(&t2, NULL, &consumer, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("main: done!\n");
  return 0;
}

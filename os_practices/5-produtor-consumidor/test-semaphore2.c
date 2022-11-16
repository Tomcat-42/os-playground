#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

#define N 5

int buffer[N];
volatile int count = 0;

// full, empty and mutex semaphores
sem_t full, empty, mutex;

void *producer() {
  int in = 0;
  for (int i = 0; i < 10000; i++) {
    // while (count == N)
    //   ;
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[in] = i;
    in = (in + 1) % N;
    // printf("producer: %d\n", i);

    count++;
    sem_post(&mutex);
    sem_post(&full);
  }

  return NULL;
}

void *consumer() {
  int out = 0;
  int d_out;

  for (int i = 0; i < 10000; i++) {

    sem_wait(&full);
    sem_wait(&mutex);

    d_out = buffer[out];
    out = (out + 1) % N;
    // printf("consumer: %d\n", d_out);

    count--;
    sem_post(&mutex);
    sem_post(&empty);
  }

  return NULL;
}

int main() {
  pthread_t t1, t2;

  // initialize semaphores
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, N);
  sem_init(&mutex, 0, 1);

  pthread_create(&t1, NULL, &producer, NULL);
  pthread_create(&t2, NULL, &consumer, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("main: done!\n");
  return 0;
}

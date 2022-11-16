#include <pthread.h>
#include <stdio.h>
#include <threads.h>

#define N 5

int buffer[N];
volatile int count = 0;

// define a mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer() {
  int in = 0;
  for (int i = 0; i < 1000; i++) {
    while (count == N)
      ;

    buffer[in] = i;
    in = (in + 1) % N;
    // printf("producer: %d\n", i);
    pthread_mutex_lock(&mutex);
    count++;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

void *consumer() {
  int out = 0;
  int d_out;

  for (int i = 0; i < 1000; i++) {
    while (count == 0)
      ;

    d_out = buffer[out];
    out = (out + 1) % N;
    // printf("consumer: %d\n", d_out);

    pthread_mutex_lock(&mutex);
    count--;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, &producer, NULL);
  pthread_create(&t2, NULL, &consumer, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("main: done!\n");
  return 0;
}

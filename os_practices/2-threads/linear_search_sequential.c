/* A simple c program that linearly searches through an array of integers */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linear_search(const int *array, int size, int value) {
  int i;
  for (i = 0; i < size; i++) {
    if (array[i] == value) {
      return i;
    }
  }
  return -1;
}

int main() {
  int i;
  int size = 1000000;
  int *array = malloc(sizeof(int) * size);
  int value = 100;
  int index;

  srand(time(NULL));
  for (i = 0; i < size; i++) {
    array[i] = rand() % 1000;
  }

  index = linear_search(array, size, value);
  if (index == -1) {
    printf("Value %d not found in array\n", value);
  } else {
    printf("Value %d found at index %d in array\n", value, index);
  }
}

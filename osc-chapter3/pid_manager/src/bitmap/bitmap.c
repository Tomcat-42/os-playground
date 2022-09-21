#include "bitmap/bitmap.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define BIT (CHAR_BIT * sizeof(unsigned char))

bitmap *bitmap_new(size_t size) {
  assert(size > 0);

  bitmap *bitmap;

  if (!(bitmap = calloc(1, sizeof(struct bitmap)))) {
    return NULL;
  }

  bitmap->size = size;
  if (!(bitmap->data = calloc(ceil((double)size / BIT), sizeof(uint8_t)))) {
    free(bitmap);
    return NULL;
  }

  return bitmap;
}

void bitmap_set(bitmap *bitmap, size_t index) {
  assert(bitmap != NULL);
  assert(index < bitmap->size);

  bitmap->data[index / 8] |= 1 << (index % 8);
}

void bitmap_clear(bitmap *bitmap, size_t index) {
  assert(bitmap != NULL);
  assert(index < bitmap->size);

  bitmap->data[index / 8] &= ~(1 << (index % 8));
}

unsigned int bitmap_get(bitmap *bitmap, size_t index) {
  assert(bitmap != NULL);
  assert(index < bitmap->size);

  return (bitmap->data[index / 8] & (1 << (index % 8))) != 0;
}

void bitmap_flip(bitmap *bitmap, size_t index) {
  assert(bitmap != NULL);
  assert(index < bitmap->size);

  bitmap->data[index / 8] ^= 1 << (index % 8);
}

int bitmap_search(bitmap *bitmap, unsigned int n) {
  assert(bitmap != NULL);

  for (size_t i = 0; i < bitmap->size; i++) {
    if (bitmap_get(bitmap, i) == n) {
      return i;
    }
  }
  return -1;
}

int bitmap_delete(bitmap *bitmap) {
  assert(bitmap != NULL);

  free(bitmap->data);
  free(bitmap);

  return 1;
}

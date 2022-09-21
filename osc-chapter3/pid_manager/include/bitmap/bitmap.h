#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Bitmap data structure
 * @param data Pointer to the bitmap data
 * @param size Size of the bitmap in bits
 */
typedef struct bitmap {
  unsigned char *data;
  size_t size;
} bitmap;

/**
 * @brief Initialize a bitmap
 * @param bitmap Bitmap to initialize
 * @param size Size of the bitmap in bits
 * @return *bitmap or NULL on error
 */
bitmap *bitmap_new(size_t size);

/**
 * @brief Set a bit in the bitmap
 * @param bitmap Bitmap to set the bit in
 * @param index Index of the bit to set
 */
void bitmap_set(bitmap *bitmap, size_t index);

/**
 * @brief Clear a bit in the bitmap
 * @param bitmap Bitmap to clear the bit in
 * @param index Index of the bit to clear
 * @return 1 on success, 0 on failure
 */
void bitmap_clear(bitmap *bitmap, size_t index);

/**
 * @brief Get a bit in the bitmap
 * @param bitmap Bitmap to get the bit from
 * @param index Index of the bit to get
 * @return 0 if the bit is not set, 1 if the bit is set
 */
unsigned int bitmap_get(bitmap *bitmap, size_t index);

/**
 * @brief Flip a bit in the bitmap
 * @param bitmap Bitmap to flip the bit in
 * @param index Index of the bit to flip
 */
void bitmap_flip(bitmap *bitmap, size_t index);

/**
 * @brief Search for a bit set as N in the bitmap
 * @param bitmap Bitmap to search in
 * @param n value of the bit to search for (0 or 1)
 * @return Index of the bit, -1 if no free bit was found
 */
int bitmap_search(bitmap *bitmap, unsigned int n);

/**
 * @brief Destroy a bitmap
 * @param bitmap Bitmap to destroy
 * @return 1 on success, 0 on failure
 */
int bitmap_delete(bitmap *bitmap);

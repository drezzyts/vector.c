#ifndef VECTOR_H
#define VECTOR_H

#ifndef VECTOR_INITIAL_CAPACITY
  #define VECTOR_INITIAL_CAPACITY 5
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

typedef struct {
  void* data;
  size_t element_size;
  size_t capacity;
  size_t size;
} vector_t;

vector_t* vector_create(size_t);
vector_t* vector_clone(const vector_t*);

void vector_insert(vector_t*, const void*, size_t);
void vector_resize(vector_t*, size_t);
void vector_push(vector_t*, const void*); 

void vector_lconcat(vector_t*, size_t, ...);
void vector_aconcat(vector_t*, size_t, const void*);
void vector_concat(vector_t*, const vector_t*);

void vector_pop(vector_t*);
void vector_shift(vector_t*);

void* vector_last(const vector_t*);
void* vector_first(const vector_t*);
void* vector_at(const vector_t*, int64_t);

void vector_resize(vector_t* vector, size_t capacity) {
  void* data = malloc(vector->element_size * capacity);
  memcpy(data, vector->data, vector->element_size * vector->size);
  
  free(vector->data);
  
  vector->capacity = capacity;
  vector->data = data;
}

#endif
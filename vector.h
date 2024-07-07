#ifndef VECTOR_H
#define VECTOR_H

#ifndef VECTOR_INITIAL_CAPACITY
  #define VECTOR_INITIAL_CAPACITY 5
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
  void* data;
  size_t element_size;
  size_t capacity;
  size_t size;
} vector_t;

vector_t* vector_create(size_t);
vector_t* vector_clone(const vector_t*);

void vector_resize(vector_t*, size_t);
void vector_push(vector_t*, void*); 
void vector_pop(vector_t*);

void* vector_at(const vector_t*, size_t);
void* vector_last(const vector_t*);
void* vector_first(const vector_t*);

vector_t* vector_create(size_t element_size) {
  vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
  vector->data = (void*) malloc(element_size * VECTOR_INITIAL_CAPACITY);
  vector->capacity = VECTOR_INITIAL_CAPACITY;
  vector->size = 0;
  vector->element_size = element_size;

  return vector;
};

vector_t* vector_clone(const vector_t* source) {
  vector_t* destination = (vector_t*) malloc(sizeof(vector_t));
  memcpy(destination, source, sizeof(vector_t));
  
  return destination; 
}

void vector_resize(vector_t* vector, size_t capacity) {
  void* data = malloc(vector->element_size * capacity);
  memcpy(data, vector->data, vector->element_size * vector->size);
  
  free(vector->data);
  
  vector->capacity = capacity;
  vector->data = data;
}

void vector_push(vector_t* vector, void* value) {
  if (vector->capacity < vector->size)
    vector_resize(vector, vector->capacity * 2);

  uint8_t* bytes = (uint8_t*) vector->data;
  memcpy(bytes + (vector->size * vector->element_size), value, vector->element_size);
  vector->size++;
}

void vector_pop(vector_t* vector) {
  if (vector->size < 1) return;

  vector->size--;

  void* data = malloc(vector->element_size * vector->size); 
  memcpy(data, vector->data, vector->element_size * vector->size);  
  free(vector->data);

  vector->data = data;

  if (vector->size <= vector->capacity / 4)
    vector_resize(vector, vector->capacity / 2);
}

void* vector_at(const vector_t* vector, size_t index) {
  if (index >= vector->size) return NULL;

  const uint8_t* bytes = (uint8_t*) vector->data;
  return (void*) (bytes + (index * vector->element_size));
};

void* vector_last(const vector_t* vector) {
  if (vector->size < 1) return NULL;

  const uint8_t* bytes = (uint8_t*) vector->data;
  return (void*) (bytes + (vector->size - 1) * (vector->element_size));
}

void* vector_first(const vector_t* vector) {
  if (vector->size < 1) return NULL;
  return vector->data;
}

#endif
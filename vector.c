#include <stdarg.h>
#include "vector.h"

vector_t* vector_create(size_t element_size) {
  vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
  vector->data = (void*) malloc(element_size * VECTOR_INITIAL_CAPACITY);
  vector->capacity = VECTOR_INITIAL_CAPACITY;
  vector->size = 0;
  vector->element_size = element_size;

  return vector;
};

vector_t* vector_clone(const vector_t* source) {
  vector_t* destination = vector_create(source->element_size);
  memcpy(destination->data, source->data, source->size * source->element_size);
  
  return destination; 
}

void vector_push(vector_t* vector, const void* value) {
  if (vector->capacity < vector->size)
    vector_resize(vector, vector->capacity * 2);

  uint8_t* bytes = (uint8_t*) vector->data;
  memcpy(bytes + (vector->size * vector->element_size), value, vector->element_size);
  vector->size++;
}

void vector_lconcat(vector_t* vector, size_t count, ...) {
  va_list elements;
  va_start(elements, count);

  for (size_t i = 0; i < count; i++)
    vector_push(vector, va_arg(elements, void*));
  
  va_end(elements);
}

void vector_aconcat(vector_t* vector, size_t size, const void* array) {
  uint8_t* bytes = (uint8_t*) array;

  for (size_t i = 0; i < size; i++)
    vector_push(vector, bytes + (i * vector->element_size));
}

void vector_concat(vector_t* destination, const vector_t* source) {
  if (destination->element_size != source->element_size) return;

  size_t dsize = destination->size * destination->element_size;
  size_t ssize = source->size * source->element_size;

  vector_resize(destination, destination->capacity + source->capacity);
  destination->size += source->size;

  uint8_t* dbytes = (uint8_t*) destination->data;
  memcpy(dbytes + dsize, 
    source->data, 
    source->size * source->element_size
  );
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

void vector_shift(vector_t* vector) {
  if (vector->size < 1) return;
  vector->size--;

  void* data = malloc(vector->element_size * vector->size);
  uint8_t* bytes = (uint8_t*) vector->data;

  memcpy(data, bytes + vector->element_size, vector->size * vector->element_size);
  free(vector->data);

  vector->data = data;

  if (vector->size <= vector->capacity / 4)
    vector_resize(vector, vector->capacity / 2);
}

void vector_insert(vector_t* vector, const void* value, size_t index) {
  if (vector->size <= index) return;
  if (vector->size >= vector->capacity) 
    vector_resize(vector, vector->capacity * 2);
  
  size_t l_size = vector->element_size * index;
  size_t r_size = vector->element_size * (vector->size - index);

  uint8_t* bytes = (uint8_t*) vector->data;
  memmove(bytes + l_size + vector->element_size, bytes + l_size, r_size);
  memcpy(bytes + l_size, value, vector->element_size);

  vector->size++;
}

void* vector_at(const vector_t* vector, int64_t index) {
  if (abs(index) > vector->size) return NULL;

  const uint8_t* bytes = (uint8_t*) vector->data;
  return (void*) (bytes + ((index < 0 ? vector->size + index : index) * vector->element_size));
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
#ifndef VECTOR_H
#define VECTOR_H

#ifndef VECTOR_INITIAL_CAPACITY
#define VECTOR_INITIAL_CAPACITY 5
#endif

#ifndef VECTOR_INT_COMPARE
#define VECTOR_INT_COMPARE __vector_int_cmp
#endif

#ifndef VECTOR_FLOAT_COMPARE
#define VECTOR_FLOAT_COMPARE __vector_float_cmp
#endif

#ifndef VECTOR_STRING_COMPARE
#define VECTOR_STRING_COMPARE __vector_string_cmp
#endif

#ifndef VECTOR_CHAR_COMPARE
#define VECTOR_CHAR_COMPARE __vector_char_cmp
#endif

#ifndef __VECTOR_EPSILON
#define __VECTOR_EPSILON 1e-5
#endif

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

typedef struct
{
  void *data;
  size_t element_size;
  size_t capacity;
  size_t size;
} vector_t;

vector_t *vector_create(size_t);
vector_t *vector_clone(const vector_t *);

void vector_insert(vector_t *, const void *, size_t);
void __vector_resize(vector_t *, size_t);
void vector_push(vector_t *, const void *);

void vector_lconcat(vector_t *, size_t, ...);
void vector_aconcat(vector_t *, size_t, const void *);
void vector_concat(vector_t *, const vector_t *);

void vector_pop(vector_t *);
void vector_shift(vector_t *);
void vector_delete(vector_t *, size_t);
void vector_remove(vector_t *vector, const void *expected, 
  bool (*compare_function)(const void *expected, const void *current));

void *vector_last(const vector_t *);
void *vector_first(const vector_t *);
void *vector_at(const vector_t *, int64_t);

void __vector_resize(vector_t *vector, size_t capacity)
{
  void *data = malloc(vector->element_size * capacity);
  memcpy(data, vector->data, vector->element_size * vector->size);

  free(vector->data);

  vector->capacity = capacity;
  vector->data = data;
}

bool __vector_int_cmp(const void* expected, const void* current) {
  if (expected == NULL || current == NULL) return false;
  return (*(int*) expected) == (*(int*) current) ? true : false;
}

bool __vector_float_cmp(const void* expected, const void* current) {
  if (expected == NULL || current == NULL) return false;
  return fabs(*(float*) expected - *(float*) current) < __VECTOR_EPSILON;
}

bool __vector_string_cmp(const void* expected, const void* current) {
  if (expected == NULL || current == NULL) return false;
  return strcmp(*(char**) expected, *(char**) current) == 0 ? true : false;
}

bool __vector_char_cmp(const void* expected, const void* current) {
  if (expected == NULL || current == NULL) return false;
  return (*(char*) expected) == (*(char*) current) ? true : false;
}

#endif
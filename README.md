# 🗃️ vector.c

Vector.c is a simple library that provides a dynamic array structure and methods to manipulate it.

> **License:** MIT

## Summary

* [Creating a vector](#creating-a-vector)
* [Inserting values into a vector](#inserting-values-into-a-vector)
* [Removing values of a vector](#removing-values-of-a-vector)
* [Getting values of a vector](#getting-values-of-a-vector)
* [Concating structures](#concating-structures)
* [Deleting specific values](#deleting-specific-values)

## Usage

To use `vector.c`, simply include the header file in your project:

```c
#include "vector.h"
```

## Methods

### Creating a vector

To create a vector in `vector.c` you can use `vector_create` or `vector_clone` functions. See the examples below:

**Prototypes:**

```c
vector_t* vector_create(size_t);
vector_t* vector_clone(const vector_t*);
```

**Examples:**

```c
// creating vectors
vector_t* int_vec = vector_create(sizeof(int));
vector_t* float_vec = vector_create(sizeof(float));
vector_t* char_vec = vector_create(sizeof(char));
vector_t* string_vec = vector_create(sizeof(char**));

// creating a clone of vector
vector_t* clone = vector_clone(vector);
```

### Inserting values into a vector

To insert values into a `vector.c` vector, you can use `vector_push` or `vector_insert` functions. See the examples bellow:

**Prototypes:**

```c
void vector_insert(vector_t*, void*, size_t);
void vector_push(vector_t*, void*);
```

**Examples:**

```c
vector_t* vector = vector_create(sizeof(int));

// ... pushing a value to the end of a vector
vector_push(vector, &(int){25});

// ... inserting a value at a specific index of a vector
vector_insert(vector, &(int){35}, 0);
```

### Removing values of a vector

To remove a value of a `vector.c` vector, you can use `vector_pop` or `vector_shift` functions. See the examples bellow:

**Prototypes:**

```c
void vector_pop(vector_t*);
void vector_shift(vector_t*);
```

**Examples:**

```c
vector_t* vector = vector_create(sizeof(int));

// ... removing the first element of a vector
vector_shift(vector);

// ... removing the last element of a vector
vector_pop(vector);
```

### Getting values of a vector

To get a value of a `vector.c` vector, you can use `vector_first`, `vector_last` or `vector_at` functions. See the examples below:

**Prototypes:**

```c
void* vector_last(const vector_t*);
void* vector_first(const vector_t*);
void* vector_at(const vector_t*, int64_t);
```

**Examples:**

```c
vector_t* vector = vector_create(sizeof(int));

// ... getting the first element of a vector
int* f1 = (int*) vector_first(vector);
int* f2 = (int*) vector_at(vector, 0);

// ... getting the last element of a vector
int* l1 = (int*) vector_last(vector);
int* l2 = (int*) vector_at(vector, -1);

// ... getting element at specific index of a vector
int* v1 = (int*) vector_at(vector, 2);
int* v2 = (int*) vector_at(vector, -3);
```

### Concating structures

To concat a structure into a `vector.c` vector, you can use `vector_concat`, `vector_aconcat` or `vector_lconcat` functions. See examples below:

**Prototypes:**

```c
void vector_lconcat(vector_t*, size_t, ...);
void vector_aconcat(vector_t*, size_t, const void*);
void vector_concat(vector_t*, const vector_t*);
```

**Examples:**

```c
vector_t* vec1 = vector_create(sizeof(int));
vector_t* vec2 = vector_clone(vec1);

// ... concating a array into a vector
vector_aconcat(vec1, 5, &(int){1, 2, 3, 4, 5});

// ... concating a list into a vector
vector_lconcat(vec2, 2, &(int){6}, &(int){7});

// ... concating a vector into a other vector
vector_concat(vec1, vec2);
```

### Deleting specific values

To remove a value into a `vector.c`, you can use `vector_remove` or `vector_delete` functions. See the examples below:

**Prototypes:**

```c
void vector_delete(vector_t*, size_t);
void vector_remove(vector_t*, const void*, bool (*)(const void*, const void*));
```

**Examples:**

```c
// ... deleting a value by index
vector_delete(vector, 1);

// ... removing a value by value comparison
vector_remove(vector, &(int){2}, VECTOR_INT_COMPARE);
vector_remove(vector, &(float){3.5}, VECTOR_FLOAT_COMPARE);
vector_remove(vector, &(char){'H'}, VECTOR_CHAR_COMPARE);
vector_remove(vector, &(char*){"Hello, World!"}, VECTOR_STRING_COMPARE);
```

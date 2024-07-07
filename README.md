# 🗃️ vector.c

Vector.c is a simple library that provides a dynamic array structure and methods to manipulate it.

> **License:** MIT

## Summary

* [Creating a vector](#creating-a-vector)
* [Inserting values into a vector](#inserting-values-into-a-vector)
* [Removing values of a vector](#removing-values-of-a-vector)
* [Getting values of a vector](#getting-values-of-a-vector)

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
// creating a int vector
vector_t* vector = vector_create(sizeof(int));

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
// creating the vector
vector_t* vector = vector_create(sizeof(int));

// pushing some values
vector_push(vector, &(int){10});
vector_push(vector, &(int){20});
vector_push(vector, &(int){30});

// getting the first element of a vector
int* f1 = (int*) vector_first(vector);
int* f2 = (int*) vector_at(vector, 0);

// getting the last element of a vector
int* l1 = (int*) vector_last(vector);
int* l2 = (int*) vector_at(vector, -1);

// getting element at specific index of a vector
int* v1 = (int*) vector_at(vector, 2);
int* v2 = (int*) vector_at(vector, -3);
```


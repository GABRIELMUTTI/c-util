#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

#include "bool.h"

struct array;

void array_init(struct array *array, size_t value_size);
void array_free(struct array *array);

void array_copy(struct array *dest, struct array *source);
void array_copy_buffer(struct array *array, void *buffer, size_t size);

void *array_get(struct array *array, size_t index);
void array_set(struct array *array, size_t index, void *value);

size_t array_get_size(struct array *array);

enum bool array_is_empty(struct array *array);

#endif

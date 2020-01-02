#ifndef RUANO_ARRAY_H
#define RUANO_ARRAY_H

#include <stddef.h>

struct array {
	size_t count;
	size_t capacity;
	size_t value_size;
	void *data;
};

void array_init(struct array *array, size_t value_size);
void array_free(struct array *array);

void array_copy(struct array *dest, struct array *source);
void array_copy_buffer(struct array *array, void *buffer, size_t capacity, size_t count);

void *array_get(struct array *array, size_t index);
void array_set(struct array *array, size_t index, void *value);

size_t array_capacity(struct array *array);
size_t array_count(struct array *array);


#endif

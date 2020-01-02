#include "array.h"

#include <stdlib.h>
#include <string.h>

void array_init(struct array *array, size_t value_size)
{
	array->count = 0;
	array->capacity = 0;
	array->value_size = value_size;
	array->data = NULL;
}

inline
void array_free(struct array *array)
{
	free(array->data);
}

void array_copy(struct array *dest, struct array *source)
{
	dest->count = source->count;
	dest->capacity = source->capacity;
	free(dest->data);
	dest->data = source->data;
}

void array_copy_buffer(struct array *array, void *buffer, size_t capacity, size_t count)
{
	memcpy(array->data, buffer, capacity);
	array->count = count;
	array->capacity = capacity;
}

inline
void *array_get(struct array *array, size_t index)
{
	return array->data + index;
}

inline
void array_set(struct array *array, size_t index, void *value)
{
	memcpy(array->data + index, value, array->value_size);
}

inline
size_t array_capacity(struct array *array)
{
	return array->capacity;
}

inline
size_t array_count(struct array *array)
{
	return array->count;
}

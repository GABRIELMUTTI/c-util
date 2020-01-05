#include "array.h"

#include <stdlib.h>
#include <string.h>

struct array {
	size_t size;
	size_t value_size;
	void *data;
};

void array_init(struct array *array, size_t value_size)
{
	array->size = 0;
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
	dest->size = source->size;
	free(dest->data);
	dest->data = source->data;
}

void array_copy_buffer(struct array *array, void *buffer, size_t size)
{
	memcpy(array->data, buffer, size);
	array->size = size;
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
size_t array_get_size(struct array *array)
{
	return array->size;
}

inline
enum bool array_is_empty(struct array *array)
{
	return (enum bool)(array->size == 0);
}

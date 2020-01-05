#include "vector.h"

#include <string.h>

#define VECTOR_GET_ELEM(vector, index)			\
	vector->array + (vector->elem_size * index)	\

/* Resizes the vector based on the allocation factor.  */
static void vector_factor_resize(struct vector *vector);

struct vector *vector_init(struct vector *vector, size_t elem_size)
{
	if (!vector) { vector = malloc(sizeof(*vector)); }
	
	vector->array = NULL;
	vector->count = 0;
	vector->elem_size = elem_size;
	vector->size = 0;
	vector->alloc_factor = VECTOR_DEFAULT_ALLOC_FACTOR;

	return vector;
}

inline void vector_free(struct vector *vector)
{
	free(vector->array);
}

void vector_push_back(struct vector *vector, void *elem)
{    
	if (vector->count == vector->size)
		vector_factor_resize(vector);

	void *start = VECTOR_GET_ELEM(vector, vector->count);
	memcpy(start, elem, vector->elem_size);

	vector->count++;
}

inline void *vector_get(struct vector *vector, size_t index)
{
	return VECTOR_GET_ELEM(vector, index);
}

void vector_set(struct vector *vector, size_t index, void *elem)
{
	void *start = VECTOR_GET_ELEM(vector, index);
	memcpy(start, elem, vector->elem_size);
}

inline void vector_set_back(struct vector *vector, void * elem)
{
	vector_set(vector, vector->count, elem);
}

static void vector_factor_resize(struct vector *vector)
{
	size_t size;
	if (vector->size == 0)
		size = vector->alloc_factor;
	else
		size = vector->alloc_factor * vector->size;
	
	vector_resize(vector, size);    
}

void *vector_create_back(struct vector *vector)
{
	if (vector->count == vector->size)
		vector_factor_resize(vector);
	
    	void *elem = VECTOR_GET_ELEM(vector, vector->count);
	vector->count++;

	return elem;
}

void vector_clone(struct vector *vector, size_t index_dest, size_t index_orig)
{
	void *dest = VECTOR_GET_ELEM(vector, index_dest);
	void *orig = VECTOR_GET_ELEM(vector, index_orig);
	memcpy(dest, orig, vector->elem_size);
}

inline void vector_remove_back(struct vector *vector)
{
	vector->count--;
}

void vector_remove_fill(struct vector *vector, size_t index)
{
	vector_clone(vector, index, vector->count - 1);
	vector_remove_back(vector);
}

void vector_fill(struct vector *vector, void *elem)
{
	for (size_t i = vector->count; i < vector->size; i++) {
		void *elem_start = VECTOR_GET_ELEM(vector, i);
		memcpy(elem_start, elem, vector->elem_size);
		vector->count++;
	}
}

void vector_resize(struct vector *vector, size_t size)
{
	vector->array = realloc(vector->array, vector->elem_size * size);

	if (vector->size > size)
		vector->count = size;

	vector->size = size;
}

void vector_set_buffer(struct vector *vector, void *buffer, size_t size)
{
	free(vector->array);
	vector->array = buffer;
	vector->size = size;
	vector->count = 0;
}

inline void vector_clear(struct vector *vector)
{
	vector->count = 0;
}

void vector_sparse_set(struct vector *vector, size_t index, void *elem)
{
	vector_set(vector, index, elem);
	vector->count++;
}

void *vector_sparse_create(struct vector *vector, size_t index)
{
	vector->count++;
	return VECTOR_GET_ELEM(vector, index);
}

inline void vector_sparse_remove(struct vector *vector)
{
	vector->count--;
}

inline void *vector_get_back(struct vector *vector)
{
	return VECTOR_GET_ELEM(vector, vector->count - 1);
}

inline
size_t vector_get_count(struct vector *vector)
{
	return vector->count;
}

void vector_copy_buffer(struct vector *vector, void *buffer, size_t count)
{
	vector_clear(vector);

	if (count > vector->size)
		vector_factor_resize(vector);

	memcpy(vector->array, buffer, count * vector->elem_size);

	vector->count = count;
}

void vector_buffer_as_ref(struct vector *vector, size_t elem_size, void *buffer, size_t count)
{
	vector->array = buffer;
	vector->elem_size = elem_size;
	vector->count = count;
	vector->size = count;
}

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define VECTOR_DEFAULT_ALLOC_FACTOR 2
#define VECTOR_INITIALIZER(_elem_size)					\
	(struct vector) {						\
		.array = NULL,						\
			.elem_size = _elem_size,			\
			.count = 0,					\
			.size = 0,					\
			.alloc_factor = VECTOR_DEFAULT_ALLOC_FACTOR	\
			}

struct vector {
	
	void *array;
	size_t elem_size;
	size_t count;
	size_t size;
	
	size_t alloc_factor;
};

struct vector *vector_init(struct vector *vector, size_t elem_size);
void vector_free(struct vector *vector);

void *vector_get(struct vector *vector, size_t index);
void *vector_create_back(struct vector *vector);
void *vector_sparse_create(struct vector *vector, size_t index);
void *vector_get_back(struct vector* vector);

void vector_push_back(struct vector *vector, void *elem);
void vector_set(struct vector *vector, size_t index, void *elem);
void vector_set_back(struct vector *vector, void *elem);
void vector_fill(struct vector *vector, void *elem);
void vector_sparse_set(struct vector *vector, size_t index, void *elem);

void vector_clone(struct vector *vector, size_t index_dest, size_t index_orig);
void vector_remove_back(struct vector *vector);
void vector_remove_fill(struct vector *vector, size_t index);
void vector_clear(struct vector *vector);
void vector_sparse_remove(struct vector *vector);

void vector_resize(struct vector *vector, size_t size);
void vector_set_buffer(struct vector *vector, void *buffer, size_t size);

size_t vector_get_count(struct vector *vector);

void vector_copy_buffer(struct vector *vector, void *buffer, size_t count);
void vector_buffer_as_ref(struct vector *vector, size_t elem_size, void *buffer, size_t count);


#endif /* VECTOR_H */


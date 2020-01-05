#include "buffer.h"

#include <math.h>

size_t calculate_capacity_to_fit(size_t capacity, size_t size, double resize_factor)
{
	double new_capacity = capacity == 0 ? 1 : capacity;
	while (new_capacity < size) {
		new_capacity *= resize_factor;
	}

	return (size_t)(ceil(new_capacity));
}

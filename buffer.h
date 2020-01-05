#ifndef RUANO_BUFFER_H
#define RUANO_BUFFER_H

#include <stddef.h>

size_t calculate_capacity_to_fit(size_t capacity, size_t size, double resize_factor);

#endif

#include "text.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "buffer.h"

#define RESIZE_FACTOR 2

char *string_get_buffer(struct string *string);
void string_free_dynamic_data(struct string *string);
void string_allocate(struct string *string);

void string_init(struct string *string)
{
	string->length = 0;
	string->dynamic_capacity = 0;
	string->dynamic_data = NULL;
}


void string_free_dynamic_data(struct string *string)
{
	free(string->dynamic_data);
	string->dynamic_data = NULL;
	string->dynamic_capacity = 0;
}

void string_copy_c_str(struct string *string, const char *const c_str)
{
	size_t c_str_length = strlen(c_str);
	string_copy_char_buffer(string, c_str, c_str_length);
}

void string_copy_char_buffer(struct string *string, const char *const char_buffer, size_t length)
{
	string->length = length;
	
	if (length == 0) {
		if (string->dynamic_data) string_free_dynamic_data(string);

	} else if (length <= STRING_STATIC_DATA_CAPACITY) {

		if (string->dynamic_data) string_free_dynamic_data(string);
		
		memcpy(string->static_data, char_buffer, length);
		
	} else {
		
		if (string->dynamic_capacity < length) {
			if (string->dynamic_data) string_free_dynamic_data(string);

			string->dynamic_capacity = calculate_capacity_to_fit(string->dynamic_capacity, length, RESIZE_FACTOR);
			string->dynamic_data = malloc(sizeof(char) * string->dynamic_capacity);
		}

		memcpy(string->dynamic_data, char_buffer, length);
	}
}

void string_copy(struct string *dest, struct string *orig)
{
	char *data;
	
	if (orig->dynamic_data) {
		data = orig->dynamic_data;
	} else {
		data = orig->static_data;
	}

	string_copy_char_buffer(dest, data, orig->length);
}

inline
void string_free(struct string *string)
{
	if (string->dynamic_data) string_free_dynamic_data(string);
}

inline
enum bool string_is_empty(struct string *string)
{
	return (enum bool)(string->length == 0);
}

inline
size_t string_get_length(struct string *string)
{
	return string->length;
}

char string_get(struct string *string, size_t index)
{
	char *buffer = string_get_buffer(string);
	return buffer[index];
}

void string_set(struct string *string, char chr, size_t index)
{
	char *buffer = string_get_buffer(string);
	buffer[index] = chr;
}

inline
char *string_get_buffer(struct string *string)
{
	return string->dynamic_data ? string->dynamic_data : string->static_data;
}

inline
enum bool string_is_in_range(struct string *string, size_t index)
{
	return index < string->length;
}

enum bool string_has_prefix(struct string *string, struct string *prefix)
{
	if (string->length < prefix->length) return BOOL_FALSE;

	char *string_buffer = string_get_buffer(string);
	char *prefix_buffer = string_get_buffer(prefix);
	
	for (size_t i = 0; i < prefix->length; i++) {
		if (string_buffer[i] != prefix_buffer[i])
			return BOOL_FALSE;
		
	}

	return BOOL_TRUE;
}

enum bool string_compare(struct string *string, struct string *other)
{
	size_t smallest_length = string->length < other->length ? string->length : other->length;
	char *string_buffer = string_get_buffer(string);
	char *other_buffer = string_get_buffer(other);
	
	for (size_t i = 0; i < smallest_length; i++) {
		if (string_buffer[i] != other_buffer[i]) return BOOL_FALSE;
	}

	return BOOL_TRUE;
}

char *string_to_c_str(struct string *string, char *c_str)
{
	char *buffer = string_get_buffer(string);

	memcpy(c_str, buffer, string->length);
	c_str[string->length] = '\0';

	return c_str;
}

void string_split(struct string *string, size_t index,
		  struct string *first, struct string *second)
{
	if (first) {
		first->dynamic_capacity = index;
		first->dynamic_data = string_get_buffer(string);
		first->length = index;
	}
	
	if (second) {
		second->dynamic_capacity = string->dynamic_capacity - index;
		second->dynamic_data = string_get_buffer(string) + index;
		second->length = string->length - index;
	}
}

void string_shift_left(struct string *string, size_t amount)
{
	string->length -= amount;
	
	if (string->dynamic_data) {
		string->dynamic_data += amount;
	} else {
		memcpy(string->static_data, string->static_data + amount, string->length);
	}
}

inline
void string_c_str_as_ref(struct string *ref, char *buffer)
{
	string_char_buffer_as_ref(ref, buffer, strlen(buffer));
}

void string_char_buffer_as_ref(struct string *ref, char *buffer, size_t length)
{
	ref->length = length;
	ref->dynamic_data = buffer;
	ref->dynamic_capacity = length;
}

void string_append(struct string *string, char chr)
{
	if (!string->dynamic_data) {
		
		string->static_data[string->length] = chr;
		
	} else {
		
		if (string->length == string->dynamic_capacity) {
			string_allocate(string);
		}

		string->dynamic_data[string->length] = chr;
	}

	string->length++;
}

void string_allocate(struct string *string)
{
	string->dynamic_capacity *= RESIZE_FACTOR;
	string->dynamic_data = realloc(string->dynamic_data, sizeof(char) * string->dynamic_capacity);
}

void string_clear(struct string *string)
{
	string->length = 0;
	string_free_dynamic_data(string);
}

enum bool string_contains_only(struct string *string, struct string *chars)
{
	for (size_t i = 0; i < string->length; i++) {
		
		enum bool contains_only = BOOL_FALSE;
		for (size_t j = 0; j < chars->length; j++) {
			
			if (string_get(string, i) == string_get(chars, j)) {
				contains_only = BOOL_TRUE;
				break;
			}
		}

		if (!contains_only) return contains_only;
	}

	return BOOL_TRUE;
}

enum bool string_contains_char(struct string *string, char chr)
{
	for (size_t i = 0; i < string->length; i++) {
		if (string_get(string, i) == chr) return BOOL_TRUE;
	}

	return BOOL_FALSE;
}

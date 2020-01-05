#ifndef TEXT_H
#define TEXT_H

#include <stddef.h>
#include "bool.h"

#define STRING_STATIC_DATA_CAPACITY 64

struct string {
	size_t length;
	char static_data[STRING_STATIC_DATA_CAPACITY];
	size_t dynamic_capacity;
	char *dynamic_data;
};

void string_init(struct string *string);

void string_copy_char_buffer(struct string *string, const char *const char_buffer, size_t length);
void string_copy_c_str(struct string *string, char const *const c_str);

void string_copy(struct string *dest, struct string *orig);
void string_free(struct string *string);

char string_get(struct string *string, size_t index);
void string_set(struct string *string, char chr, size_t index);
enum bool string_compare(struct string *string, struct string *other);

size_t string_get_length(struct string *string);
enum bool string_is_empty(struct string *string);
enum bool string_is_in_range(struct string *string, size_t index);

enum bool string_has_prefix(struct string *string, struct string *prefix);

char *string_to_c_str(struct string *string, char *c_str);
void string_split(struct string *string, size_t index,
		  struct string *first, struct string *second);

void string_shift_left(struct string *string, size_t amount);

void string_c_str_as_ref(struct string *ref, char *buffer);
void string_char_buffer_as_ref(struct string* ref, char *buffer, size_t length);

void string_append(struct string *string, char chr);
void string_clear(struct string *string);
enum bool string_contains_only(struct string *string, struct string *chars);
enum bool string_contains_char(struct string *string, char chr);



#endif

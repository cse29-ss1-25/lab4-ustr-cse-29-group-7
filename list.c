#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "list.h"

/*
Returns an empty list of initial_capacity
*/
List new_list(int32_t initial_capacity) {
    List list;
    list.size = 0;
    list.capacity = initial_capacity;
    list.data = malloc(initial_capacity * sizeof(struct UStr));
    return list;
}

/*
Initializes an list of length size with elements from array
*/
List new_list_from_array(struct UStr* array, int32_t size) {
    List list = new_list(size);
    for (int32_t i = 0; i < size; i++) {
        list.data[i] = array[i];
    }
    list.size = size;
    return list;
}


/*
Given a list of strings and a separator string, returns a single string 
containing all the strings in list joined by the separator.
*/
UStr join(List* list, UStr separator) {
	if (list->size == 0) {
		return new_ustr("");
	}

	int32_t total_bytes = 0;
	for (int32_t i = 0; i < list->size; ++i) {
		total_bytes += list->data[i].bytes;
	}
	total_bytes += separator.bytes * (list->size-1);
	char *buffer = malloc(total_bytes+1);
	char *p = buffer;
	
	memcpy(p, list->data[0].contents, list->data[0].bytes);
	p += list->data[0].bytes;
	
	for (int32_t i = 1; i < list->size; ++i) {
		memcpy(p, separator.contents, separator.bytes);
		p += separator.bytes;

		memcpy(p, list->data[i].contents, list->data[i].bytes);
		p+= list->data[i].bytes;

	}
	*p = '\0';
	UStr result = new_ustr(buffer);
	free(buffer);
	return result;
}

/*
Inserts string s into list at index s, shifting elements to the right.
Expands the list's capacity if necessary (double the capacity, or set to 1 if 0).

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t insert(List* list, UStr s, int32_t index) {
    // TODO: implement this

}

/*
Removes the element at the given index and shifts all subsequent elements left.

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t listRemoveAt(List* list, int32_t index) {
    // TODO: implement this

}

static void check_capacity(List *l) {

	if (l->size == l->capacity) {
		int32_t new_cap = l->capacity * 2;
		l->data = realloc(l->data, sizeof(UStr)*new_cap);
		l->capacity = new_cap;
	}
}

static void append(List *parts, UStr s) {
    check_capacity(parts);
    parts->data[parts->size++] = s;
}
/*
Splits the given string s into substrings separated by the given delimiter string.

Returns a List of String objects, each containing a segment between delimiters.

If the delimiter is the empty string, return a list containing the original 
string as a single element.

If the input string ends with the delimiter, include an empty string at the 
end of the result.

Note that the delimiter could be of a length of more than 1 character
*/
List split(UStr s, UStr separator) {
	List parts = new_list(4);
	if (separator.bytes == 0) {
		append(&parts, new_ustr(s.contents));
		return parts;
	}
	char* cur = s.contents;
	char* match;
	int32_t sep_len = separator.bytes;

	while((match = strstr(cur, separator.contents)) != NULL) {
		int32_t chunk_len = match - cur;
		char* tmp = malloc(chunk_len + 1);
		memcpy(tmp, cur, chunk_len);
		tmp[chunk_len] = '\0';
		UStr piece = new_ustr(tmp);
		free(tmp);

		append(&parts, piece);
		cur = match+sep_len;
	}
	append(&parts, new_ustr(cur));
	return parts;
}


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this

}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	int total = strlen(s1.contents) + strlen(s2.contents);
	char* memory = malloc(total + 1);

	strcpy(memory, s1.contents);
	strcat(memory, s2.contents);

	UStr result = new_ustr(memory);

	free(memory);
	
	return result;
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 



Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this
	if (index < 0 || index >= s.codepoints) {
		return new_ustr(s.contents);
	}
		
	int32_t pos = bi_of_cpi(s.contents, index);;
	int32_t cp_size = utf8_codepoint_size(s.contents[pos]);;

	if (pos < 0|| pos >= s.bytes) return s;
	if (cp_size <= 0) return s;

	char* new_content = malloc(s.bytes - cp_size + 1);
	int32_t new_len = s.bytes - cp_size;

	strncpy(new_content, s.contents, pos);

	strcpy(new_content + pos, s.contents + pos + cp_size);

	UStr result = new_ustr(new_content);
	free(new_content);

	return result;
}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}


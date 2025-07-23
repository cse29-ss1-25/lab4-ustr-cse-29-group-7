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

	if (start >= s.codepoints || end == start || start < 0 || end < 0){
		UStr empty = new_ustr("");
		return empty;
	}

	char* buffer = calloc(sizeof(UStr), len(s) + 1);
	int buffer_i = 0;
	int c_point = 0;
	int i = 0;

	// go to start
	while (c_point < start){
		char c = s.contents[i];
		if ((c & 0b10000000) == 0b00000000){i += 1;}
                else if ((c & 0b11100000) == 0b11000000){i += 2;}
                else if ((c & 0b11110000) == 0b11100000){i += 3;}
                else if ((c & 0b11111000) == 0b11110000){i += 4;}
                c_point++;
	}

	// start getting substring to buffer
        while (c_point < end && c_point < s.codepoints) {
                char c = s.contents[i];
                int len = 0;

                if ((c & 0b10000000) == 0b00000000){len = 1;}
                else if ((c & 0b11100000) == 0b11000000){len = 2;}
                else if ((c & 0b11110000) == 0b11100000){len = 3;}
                else if ((c & 0b11111000) == 0b11110000){len = 4;}

                for (int j = 0; j < len; j++){
                        buffer[buffer_i] = s.contents[i + j];
                        buffer_i++;
                }

                i += len;
                c_point++;
        }

	buffer[buffer_i] = 0;
	UStr new = new_ustr(buffer);

	// free what's in buffer 
	free(buffer);
	// free_ustr(s);

	return new;
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this

}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

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


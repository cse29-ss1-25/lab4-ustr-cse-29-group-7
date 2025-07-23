#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ustr.h"

/*
Run in a loop, taking in a a string, print the reverse of that string
Prints out the substring of the input string from index start to index end
*/
int main() {
    char input[256];
    while (fgets(input, sizeof(input), stdin)) {
        // Remove newline character if present
        size_t l = strlen(input);
        if (l > 0 && input[l - 1] == '\n') {
            input[l - 1] = '\0';
        }
        // Parse out from input the string and the space-separated
        // start and end indices
        
        UStr s = new_ustr(input);
        UStr reverse_s = reverse(s);

        print_ustr(reverse_s);
        printf("\n");

        free_ustr(reverse_s);
        free_ustr(s);
    }
    return 0;
}

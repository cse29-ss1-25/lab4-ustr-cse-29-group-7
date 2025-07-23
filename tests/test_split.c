// tests/test_split.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"
#include "ustr.h"

// Helper to run one test case
static void run_split_test(
    const char *input,
    const char *sep,
    const char *expected[],
    int expected_count
) {
    // Wrap inputs
    UStr s         = new_ustr((char*)input);
    UStr separator = new_ustr((char*)sep);

    // Call split()
    List parts = split(s, separator);

    // Check size
    assert(parts.size == expected_count && "split: unexpected number of parts");

    // Check each substring
    for (int i = 0; i < expected_count; i++) {
        const char *got = parts.data[i].contents;
        assert(strcmp(got, expected[i]) == 0 && "split: substring mismatch");
    }

    // Clean up
    free_ustr(s);
    free_ustr(separator);
    for (int i = 0; i < parts.size; i++) {
        free_ustr(parts.data[i]);
    }
    free(parts.data);
}

int main(void) {
    // 1) Simple delimiter
    {
        const char *exp[] = { "a", "b", "c" };
        run_split_test("a,b,c", ",", exp, 3);
    }

    // 2) Multi‑char delimiter
    {
        const char *exp[] = { "foo", "bar", "baz" };
        run_split_test("foo<>bar<>baz", "<>", exp, 3);
    }

    // 3) Separator at ends → leading/trailing empty
    {
        const char *exp[] = { "", "x", "y", "" };
        run_split_test("-x-y-", "-", exp, 4);
    }

    // 4) Consecutive delimiters → empty between
    {
        const char *exp[] = { "one", "", "two" };
        run_split_test("one||two", "|", exp, 3);
    }

    // 5) Empty separator → whole string
    {
        const char *exp[] = { "hello world" };
        run_split_test("hello world", "", exp, 1);
    }

    printf("All split tests passed!\n");
    return 0;
}


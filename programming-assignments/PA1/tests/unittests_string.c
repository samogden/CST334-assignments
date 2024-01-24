
#include <criterion/criterion.h>
#include <limits.h>
#include "../src/student_code.h"


Test(String, get_str_length, .disabled=false) {
    char test_str1[] = "hello";
    char test_str2[] = "out";
    char test_str3[] = "there";
    cr_assert(get_str_length(test_str1) == strlen(test_str1));
    cr_assert(get_str_length(test_str2) == strlen(test_str2));
    cr_assert(get_str_length(test_str3) == strlen(test_str3));
}

Test(String, copy_str, .disabled=false) {
    char test_str[] = "hello";
    cr_assert(test_str != copy_str(test_str));
    cr_assert(strcmp(test_str, copy_str(test_str)) == 0);
}

Test(String, truncate_str, .disabled=false) {
    int canary_before = INT_MAX;
    char test_str[] = "hello";
    int canary_after = INT_MAX;

    // Nothing should change
    truncate_string(test_str, strlen(test_str));
    cr_assert(strcmp(test_str, "hello") == 0);

    // We shouldn't touch the canaries
    truncate_string(test_str, strlen(test_str)+1);
    cr_assert(strcmp(test_str, "hello") == 0);
    cr_assert(canary_before == INT_MAX);
    cr_assert(canary_after == INT_MAX);

    // We do cut down the length
    truncate_string(test_str, strlen(test_str)-1);
    cr_assert(strcmp(test_str, "hell") == 0);
}

Test(String, to_uppercase, .disabled=false) {
    char test_str[] = "HeLlo";
    to_uppercase(test_str);
    for (int i = 0; i < strlen(test_str); i++) {
        cr_assert(test_str[i] >= 'A' && test_str[i] <= 'Z');
    }
}

Test(String, to_lowercase, .disabled=false) {
    char test_str[] = "HeLlo";
    to_lowercase(test_str);
    for (int i = 0; i < strlen(test_str); i++) {
        cr_assert(test_str[i] >= 'a' && test_str[i] <= 'z');
    }
}

Test(String, find_first_index, .disabled=false) {
    char test_str[] = "helLo";
    cr_assert(find_first_index(test_str, 'l') == 2);
}

Test(String, find_last_index, .disabled=false) {
    char test_str[] = "helLo";
    // Question: What is this unit test actually testing?  What implications are there?
    cr_assert(find_last_index(test_str, 'l') == 3);
}
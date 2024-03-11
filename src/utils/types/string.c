#include "string.h"

#include <stdio.h>
#include <stdlib.h>

// PUBLIC
string concat(string s1, string s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

string as_string(long long int number) {
    int length = snprintf(NULL, 0, "%lld", number);
    char* result = malloc(length + 1);
    sprintf(result, "%lld", number);
    return result;
}

string as_string_len(long long int number, int len) {
    int length = snprintf(NULL, 0, "%0*lld", len, number);
    char* result = malloc(length + 1);
    sprintf(result, "%0*lld", len, number);
    return result;
}
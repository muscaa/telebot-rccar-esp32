#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

string format(string format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    char* result = malloc(length + 1);
    va_start(args, format);
    vsprintf(result, format, args);
    va_end(args);
    return result;
}

string_array new_string_array_sentinel(string str, ...) {
    string_array result;
    result.length = 0;
    result.values = malloc(sizeof(string));
    result.values[0] = NULL;

    va_list args;
    va_start(args, str);
    while (str) {
        result.values = realloc(result.values, (result.length + 2) * sizeof(string)); // one more
        result.values[result.length++] = str;
        result.values[result.length] = NULL;

        str = va_arg(args, string);
    }
    va_end(args);

    return result;
}
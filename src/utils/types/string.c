#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../defines.h"

impl_arraydef(string);

override
string concat(string s1, string s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    string result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

override
string as_string(long long int number) {
    int length = snprintf(NULL, 0, "%lld", number);
    string result = malloc(length + 1);
    sprintf(result, "%lld", number);
    return result;
}

override
string as_string_len(long long int number, int len) {
    int length = snprintf(NULL, 0, "%0*lld", len, number);
    string result = malloc(length + 1);
    sprintf(result, "%0*lld", len, number);
    return result;
}

override
string format(string format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    string result = malloc(length + 1);
    va_start(args, format);
    vsprintf(result, format, args);
    va_end(args);
    return result;
}

override
string copy(string s) {
    return strdup(s);
}

override
void string_to_bytes(string s, byte* bytes) {
    memcpy(bytes, s, strlen(s));
}

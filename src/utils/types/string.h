#pragma once

#include <string.h>

#define new_string_array(...) new_string_array_sentinel(__VA_ARGS__, NULL)

typedef const char* string;

typedef struct {
    int length;
    string* values;
} string_array;

string concat(string s1, string s2);

string as_string(long long int number);

string as_string_len(long long int number, int len);

string format(string format, ...);

string_array new_string_array_sentinel(string str, ...);
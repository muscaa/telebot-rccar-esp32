#pragma once

#include <string.h>

#include "../array/array.h"
#include "byte.h"

typedef char* string;

arraydef(string);

string concat(string s1, string s2);

string as_string(long long int number);

string as_string_len(long long int number, int len);

string format(string format, ...);

string copy(string s);

void string_to_bytes(string s, byte* bytes);

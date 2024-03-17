#pragma once

#if defined(_WIN32)
    #define WIN 1
#elif defined(__unix__)
    #define UNIX 1
#endif

#include "../types/byte.h"

void system_date(byte* day, byte* month, int* year);

void system_time(byte* hour, byte* minute);

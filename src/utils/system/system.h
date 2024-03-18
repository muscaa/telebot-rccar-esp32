#pragma once

#if defined(_WIN32)
    #define WIN 1
#elif defined(__unix__)
    #define UNIX 1
#endif

#include "../types/byte.h"

extern int exit_code;

bool system_running();

void system_exit(int code);

void system_date(byte* day, byte* month, int* year);

void system_time(byte* hour, byte* minute);

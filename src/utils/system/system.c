#include "system.h"

#include <time.h>

#include "../defines.h"

override
void system_date(byte* day, byte* month, int* year) {
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    *day = timeinfo->tm_mday;
    *month = timeinfo->tm_mon + 1;
    *year = timeinfo->tm_year + 1900;
}

override
void system_time(byte* hour, byte* minute) {
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    *hour = timeinfo->tm_hour;
    *minute = timeinfo->tm_min;
}
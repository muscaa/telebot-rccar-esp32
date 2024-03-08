#include "date_time.h"

date new_date(int day, int month, int year) {
    return (date) { day, month, year };
}

time new_time(int hour, int minute) {
    return (time) { hour, minute };
}

bool is_leap_year(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return year % 4 == 0;
}
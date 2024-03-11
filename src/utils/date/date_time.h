#pragma once

#include <stdbool.h>

#include "../types/byte.h"

#define MONTH_JANUARY 1
#define MONTH_FEBRUARY 2
#define MONTH_MARCH 3
#define MONTH_APRIL 4
#define MONTH_MAY 5
#define MONTH_JUNE 6
#define MONTH_JULY 7
#define MONTH_AUGUST 8
#define MONTH_SEPTEMBER 9
#define MONTH_OCTOBER 10
#define MONTH_NOVEMBER 11
#define MONTH_DECEMBER 12

#define DATE_TYPE_DAY 0
#define DATE_TYPE_MONTH 1
#define DATE_TYPE_YEAR 2

#define TIME_TYPE_HOUR 0
#define TIME_TYPE_MINUTE 1

typedef struct {
    byte day;
    byte month;
    int year;
} date;

typedef struct {
    byte hour;
    byte minute;
} time;

date new_date(int day, int month, int year);

time new_time(int hour, int minute);

bool is_leap_year(int year);

int get_month_days(int month, int year);

int compare_date_time(date date1, time time1, date date2, time time2);

void date_increment(int type, date *date);

void date_decrement(int type, date *date);

void time_increment(int type, time *time);

void time_decrement(int type, time *time);
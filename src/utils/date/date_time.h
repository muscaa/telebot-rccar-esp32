#pragma once

#include <stdbool.h>

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

#define DAYS_JANUARY 31
#define DAYS_FEBRUARY 28 // 29
#define DAYS_MARCH 31
#define DAYS_APRIL 30
#define DAYS_MAY 31
#define DAYS_JUNE 30
#define DAYS_JULY 31
#define DAYS_AUGUST 31
#define DAYS_SEPTEMBER 30
#define DAYS_OCTOBER 31
#define DAYS_NOVEMBER 30
#define DAYS_DECEMBER 31

typedef struct {
    int day;
    int month;
    int year;
} date;

typedef struct {
    int hour;
    int minute;
} time;

date new_date(int day, int month, int year);

time new_time(int hour, int minute);

bool is_leap_year(int year);
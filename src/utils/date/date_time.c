#include "date_time.h"

#include <stdio.h>

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

int days[] = {
    DAYS_JANUARY,
    DAYS_FEBRUARY,
    DAYS_MARCH,
    DAYS_APRIL,
    DAYS_MAY,
    DAYS_JUNE,
    DAYS_JULY,
    DAYS_AUGUST,
    DAYS_SEPTEMBER,
    DAYS_OCTOBER,
    DAYS_NOVEMBER,
    DAYS_DECEMBER
};

// PRIVATE
int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int clamp_bounds(int value, int min, int max) {
    if (value < min) return max;
    if (value > max) return min;
    return value;
}

// PUBLIC
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

int get_month_days(int month, int year) {
    return month == MONTH_FEBRUARY && is_leap_year(year) ? 29 : days[month - 1];
}

int date_time_len;
byte date_time_value[8];

void write_date_time_byte(byte b) {
    date_time_value[date_time_len++] = b;
}

byte read_date_time_byte() {
    return date_time_value[date_time_len++];
}

long date_time_to_long(date d, time t) {
    date_time_len = 0;
    int_to_bytes(d.year, write_date_time_byte);
    date_time_value[date_time_len++] = d.month;
    date_time_value[date_time_len++] = d.day;
    date_time_value[date_time_len++] = t.hour;
    date_time_value[date_time_len++] = t.minute;
    date_time_len = 0;
    return bytes_to_long(read_date_time_byte);
}

int compare_date_time(date date1, time time1, date date2, time time2) {
    long l1 = date_time_to_long(date1, time1);
    long l2 = date_time_to_long(date2, time2);
    
    if (l1 < l2) return -1;
    if (l1 > l2) return 1;
    return 0;
}

void date_increment(int type, date *date) {
    switch (type) {
        case DATE_TYPE_DAY:
            date->day = clamp_bounds(date->day + 1, 1, get_month_days(date->month, date->year));
            break;
        case DATE_TYPE_MONTH:
            date->month = clamp_bounds(date->month + 1, 1, 12);
            date->day = clamp(date->day, 1, get_month_days(date->month, date->year));
            break;
        case DATE_TYPE_YEAR:
            date->year++;
            date->day = clamp(date->day, 1, get_month_days(date->month, date->year));
            break;
    }
}

void date_decrement(int type, date *date) {
    switch (type) {
        case DATE_TYPE_DAY:
            date->day = clamp_bounds(date->day - 1, 1, get_month_days(date->month, date->year));
            break;
        case DATE_TYPE_MONTH:
            date->month = clamp_bounds(date->month - 1, 1, 12);
            date->day = clamp(date->day, 1, get_month_days(date->month, date->year));
            break;
        case DATE_TYPE_YEAR:
            date->year--;
            date->day = clamp(date->day, 1, get_month_days(date->month, date->year));
            break;
    }
}

void time_increment(int type, time *time) {
    switch (type) {
        case TIME_TYPE_HOUR:
            time->hour = clamp_bounds(time->hour + 1, 0, 23);
            break;
        case TIME_TYPE_MINUTE:
            time->minute = clamp_bounds(time->minute + 1, 0, 59);
            break;
    }
}

void time_decrement(int type, time *time) {
    switch (type) {
        case TIME_TYPE_HOUR:
            time->hour = clamp_bounds(time->hour - 1, 0, 23);
            break;
        case TIME_TYPE_MINUTE:
            time->minute = clamp_bounds(time->minute - 1, 0, 59);
            break;
    }
}
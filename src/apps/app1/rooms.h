#pragma once

#include "../../utils/utils.h"

#define CAPACITY_LOWER 0
#define CAPACITY_EQUAL 1
#define CAPACITY_HIGHER 2

typedef struct {
    date date_from;
    time time_from;
    date date_to;
    time time_to;
} booking;

typedef struct {
    string name;
    int capacity;
    int bookings_length;
    booking* bookings;
} room;

typedef struct {
    bool set;
    string name;
} name_filter;

typedef struct {
    bool set;
    int capacity;
    int mode;
} capacity_filter;

typedef struct {
    bool set;
    date date_from;
    time time_from;
    date date_to;
    time time_to;
} availability_filter;

void _load_rooms();

int _get_rooms_length();

bool _add_room(string name, int capacity);

void _delete_room(room r);

bool _book_room(room r, date date_from, time time_from, date date_to, time time_to);

room _get_room(int index);

bool _room_exists(string name);

int _get_filtered_rooms_length();

room _get_filtered_room(int index);

void _cancel_booking(room r, booking b);

void _filter_clear();

void _filter_rooms_by_name(name_filter filter);

void _filter_rooms_by_capacity(capacity_filter filter);

void _filter_rooms_by_availability(availability_filter filter);

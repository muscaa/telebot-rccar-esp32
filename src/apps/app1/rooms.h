#pragma once

#include "../../utils/utils.h"

#define CAPACITY_LOWER 0
#define CAPACITY_EQUAL 1
#define CAPACITY_HIGHER 2

typedef struct {
    date date;
    time time;
} booking;

typedef struct {
    string name;
    int capacity;
    int bookings_length;
    booking* bookings;
} room;

typedef struct {
    string name;
} name_filter;

typedef struct {
    int capacity;
    int mode;
} capacity_filter;

typedef struct {
    date date;
    time time;
} availability_filter;

//void save_rooms();

void load_rooms();

int get_rooms_length();

bool add_room(string name, int capacity);

room get_room(int index);

bool room_exists(string name);

room* filter_rooms_by_name(room* start_rooms, int start_rooms_length, int* result_length, name_filter filter);

room* filter_rooms_by_capacity(room* start_rooms, int start_rooms_length, int* filter_length, capacity_filter filter);

room* filter_rooms_by_availability(room* start_rooms, int start_rooms_length, int* filter_length, availability_filter filter);
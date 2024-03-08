#pragma once

#include "../../utils/utils.h"

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

int get_rooms_length();

void add_room(string name, int capacity);

room get_room(int index);
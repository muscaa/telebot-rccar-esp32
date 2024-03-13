#pragma once

#include "../../utils/utils.h"

typedef struct {
    string title;
    string author;
    int types_length;
    string types[];
} book;

void load_books();

int get_books_length();

bool add_book(string name, int capacity);

void delete_book(book b);

bool book_room(book b, date date_from, time time_from, date date_to, time time_to);

book get_book(int index);

bool book_exists(string name);

/*int get_filtered_rooms_length();

room get_filtered_room(int index);

void cancel_booking(room r, booking b);

void filter_clear();

void filter_rooms_by_name(name_filter filter);

void filter_rooms_by_capacity(capacity_filter filter);

void filter_rooms_by_availability(availability_filter filter);*/
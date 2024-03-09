#include "rooms.h"

#include "main.h"
#include <stdlib.h>

#define CONFIG_FILE CONFIG_DIR "rooms.dat" // TODO mkdirs before fopen

int rooms_length = 0;
room* rooms;

int filtered_rooms_length = -1;
room* filtered_rooms;

// PRIVATE
bool init_filter() {
    if (filtered_rooms_length == -1) {
        filtered_rooms = malloc(rooms_length * sizeof(room));
        memcpy(filtered_rooms, rooms, rooms_length * sizeof(room));
        filtered_rooms_length = rooms_length;
        return true;
    }
    return false;
}

void save_rooms() {
    string parent = file_parent(CONFIG_FILE);
    if (parent != NULL) dir_create(parent);

    config_writer w = push_save_config(CONFIG_FILE);
    w.Int(rooms_length);
    for (int i = 0; i < rooms_length; i++) {
        room room = rooms[i];

        w.LenString(room.name);
        w.Int(room.capacity);

        w.Int(room.bookings_length);
        for (int j = 0; j < room.bookings_length; j++) {
            booking booking = room.bookings[j];

            w.Int(booking.date.day);
            w.Int(booking.date.month);
            w.Int(booking.date.year);

            w.Int(booking.time.hour);
            w.Int(booking.time.minute);
        }
    }
    pop_save_config();
}

// PUBLIC
void load_rooms() {
    if (rooms_length != 0) { // free memory
        for (int i = 0; i < rooms_length; i++) {
            if (rooms[i].bookings_length != 0) {
                free(rooms[i].bookings);
            }
        }
        free(rooms);
    }
    if (!file_exists(CONFIG_FILE)) return;

    config_reader r = push_load_config(CONFIG_FILE);
    rooms_length = r.Int();
    if (rooms_length != 0) {
        rooms = malloc((rooms_length + 1) * sizeof(room));
        for (int i = 0; i < rooms_length; i++) {
            room room;

            room.name = r.LenString();
            room.capacity = r.Int();

            room.bookings_length = r.Int();
            if (room.bookings_length != 0) {
                room.bookings = malloc(room.bookings_length * sizeof(booking));
                for (int j = 0; j < room.bookings_length; j++) {
                    booking booking;

                    booking.date.day = r.Int();
                    booking.date.month = r.Int();
                    booking.date.year = r.Int();

                    booking.time.hour = r.Int();
                    booking.time.minute = r.Int();

                    room.bookings[j] = booking;
                }
            }

            rooms[i] = room;
        }
    }
    pop_load_config();
}

int get_rooms_length() {
    return rooms_length;
}

bool add_room(string name, int capacity) {
    load_rooms();
    if (rooms_length == 0) {
        rooms = malloc(sizeof(room)); // 1 room
    }

    if (room_exists(name)) return false;

    room room;
    room.name = name;
    room.capacity = capacity;
    room.bookings_length = 0;
    rooms[rooms_length++] = room;

    save_rooms();
    return true;
}

room get_room(int index) {
    return rooms[index];
}

bool room_exists(string name) {
    for (int i = 0; i < rooms_length; i++) {
        if (strcmp(rooms[i].name, name) == 0) return true;
    }
    return false;
}

int get_filtered_rooms_length() {
    return filtered_rooms_length;
}

room get_filtered_room(int index) {
    return filtered_rooms[index];
}

void filter_clear() {
    if (filtered_rooms_length != -1) {
        free(filtered_rooms);
        filtered_rooms = NULL;
        filtered_rooms_length = -1;
    }
}

void filter_rooms_by_name(name_filter filter) {
    if (!init_filter() && filtered_rooms_length == 0) return;
    if (!filter.set) return;
    int new_filtered_rooms_length = 0;
    for (int i = 0; i < filtered_rooms_length; i++) {
        room r = filtered_rooms[i];

        if (strstr(r.name, filter.name)) {
            filtered_rooms[new_filtered_rooms_length++] = r;
        }
    }
    filtered_rooms = realloc(filtered_rooms, new_filtered_rooms_length * sizeof(room));;
    filtered_rooms_length = new_filtered_rooms_length;
}

void filter_rooms_by_capacity(capacity_filter filter) {
    if (!init_filter() && filtered_rooms_length == 0) return;
    if (!filter.set) return;
    int new_filtered_rooms_length = 0;
    for (int i = 0; i < filtered_rooms_length; i++) {
        room r = filtered_rooms[i];

        switch (filter.mode) {
            case CAPACITY_LOWER:
                if (r.capacity <= filter.capacity) {
                    filtered_rooms[new_filtered_rooms_length++] = r;
                }
                break;
            case CAPACITY_EQUAL:
                if (r.capacity == filter.capacity) {
                    filtered_rooms[new_filtered_rooms_length++] = r;
                }
                break;
            case CAPACITY_HIGHER:
                if (r.capacity >= filter.capacity) {
                    filtered_rooms[new_filtered_rooms_length++] = r;
                }
                break;
        }
    }
    filtered_rooms = realloc(filtered_rooms, new_filtered_rooms_length * sizeof(room));;
    filtered_rooms_length = new_filtered_rooms_length;
}

void filter_rooms_by_availability(availability_filter filter) {
    if (!init_filter() && filtered_rooms_length == 0) return;
    if (!filter.set) return;
    int new_filtered_rooms_length = 0;
    for (int i = 0; i < filtered_rooms_length; i++) {
        room r = filtered_rooms[i];

        // TODO
    }
    filtered_rooms = realloc(filtered_rooms, new_filtered_rooms_length * sizeof(room));;
    filtered_rooms_length = new_filtered_rooms_length;
}
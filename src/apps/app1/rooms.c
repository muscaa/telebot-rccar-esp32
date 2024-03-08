#include "rooms.h"

#define CONFIG "meeting_rooms_reservation/rooms.dat" // TODO mkdirs before fopen

int rooms_length = 0;
room* rooms;

// PRIVATE
void save_rooms() {
    config_writer w = push_save_config(CONFIG);
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

void load_rooms() {
    if (rooms_length != 0) { // free memory
        for (int i = 0; i < rooms_length; i++) {
            if (rooms[i].bookings_length != 0) {
                free(rooms[i].bookings);
            }
        }
        free(rooms);
    }
    if (!file_exists(CONFIG)) return;

    config_reader r = push_load_config(CONFIG);
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

// PUBLIC
int get_rooms_length() {
    if (rooms_length == 0) load_rooms();
    return rooms_length;
}

void add_room(string name, int capacity) {
    if (rooms_length == 0) {
        rooms = malloc(sizeof(room)); // 1 room
    }

    room room;
    room.name = name;
    room.capacity = capacity;
    room.bookings = 0;
    rooms[rooms_length++] = room;

    save_rooms();
    load_rooms();
}

room get_room(int index) {
    return rooms[index];
}
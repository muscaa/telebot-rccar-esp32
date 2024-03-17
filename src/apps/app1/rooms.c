#include "rooms.h"

#define CONFIG_DIR "meeting_rooms_reservation/"
#define CONFIG_FILE CONFIG_DIR "rooms.dat" // TODO mkdirs before fopen

/*private int rooms_length = 0;
private room* rooms;

private int filtered_rooms_length = -1;
private room* filtered_rooms;

private bool init_filter() {
    if (filtered_rooms_length == -1) {
        filtered_rooms = malloc(rooms_length * sizeof(room));
        memcpy(filtered_rooms, rooms, rooms_length * sizeof(room));
        filtered_rooms_length = rooms_length;
        return true;
    }
    return false;
}

private int find_room(string name) {
    for (int i = 0; i < rooms_length; i++) {
        if (strcmp(rooms[i].name, name) == 0) return i;
    }
    return -1;
}

private bool is_room_available(room room, date date_from, time time_from, date date_to, time time_to) {
    for (int i = 0; i < room.bookings_length; i++) {
        booking b = room.bookings[i];

        if (compare_date_time(date_from, time_from, b.date_from, b.time_from) == 0
                && compare_date_time(date_to, time_to, b.date_to, b.time_to) == 0) {
            return false;
        }
        if (compare_date_time(date_from, time_from, b.date_from, b.time_from) >= 0
                && compare_date_time(date_from, time_from, b.date_to, b.time_to) < 0) {
            return false;
        }
        if (compare_date_time(date_to, time_to, b.date_from, b.time_from) > 0
                && compare_date_time(date_to, time_to, b.date_to, b.time_to) <= 0) {
            return false;
        }
    }
    return true;
}

private void save_rooms() {
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

            w.Byte(booking.date_from.day);
            w.Byte(booking.date_from.month);
            w.Int(booking.date_from.year);

            w.Byte(booking.time_from.hour);
            w.Byte(booking.time_from.minute);

            w.Byte(booking.date_to.day);
            w.Byte(booking.date_to.month);
            w.Int(booking.date_to.year);

            w.Byte(booking.time_to.hour);
            w.Byte(booking.time_to.minute);
        }
    }
    pop_save_config();
}

override
void load_rooms() {
    if (rooms_length != 0) { // free memory
        for (int i = 0; i < rooms_length; i++) {
            if (rooms[i].bookings_length != 0) {
                free(rooms[i].bookings);
            }
        }
        free(rooms);
        rooms_length = 0;
    }
    if (!file_exists(CONFIG_FILE)) {
        rooms = malloc((rooms_length + 1) * sizeof(room));
        return;
    }

    config_reader r = push_load_config(CONFIG_FILE);
    rooms_length = r.Int();
    rooms = malloc((rooms_length + 1) * sizeof(room));
    for (int i = 0; i < rooms_length; i++) {
        room room;

        room.name = r.LenString();
        room.capacity = r.Int();

        room.bookings_length = r.Int();
        room.bookings = malloc((room.bookings_length + 1) * sizeof(booking));
        for (int j = 0; j < room.bookings_length; j++) {
            booking booking;

            booking.date_from.day = r.Byte();
            booking.date_from.month = r.Byte();
            booking.date_from.year = r.Int();

            booking.time_from.hour = r.Byte();
            booking.time_from.minute = r.Byte();

            booking.date_to.day = r.Byte();
            booking.date_to.month = r.Byte();
            booking.date_to.year = r.Int();

            booking.time_to.hour = r.Byte();
            booking.time_to.minute = r.Byte();

            room.bookings[j] = booking;
        }

        rooms[i] = room;
    }
    pop_load_config();
}

override
int get_rooms_length() {
    return rooms_length;
}

override
bool add_room(string name, int capacity) {
    load_rooms();
    if (room_exists(name)) {
        return false;
    }

    room room;
    room.name = name;
    room.capacity = capacity;
    room.bookings_length = 0;
    rooms[rooms_length++] = room;

    save_rooms();
    return true;
}

override
void delete_room(room r) {
    int index = find_room(r.name);
    if (index == -1) return;

    //memcpy(rooms + (index * sizeof(room)), rooms + ((index + 1) * sizeof(room)), (rooms_length - index - 1) * sizeof(room)); // doesnt work, weird..
    memcpy(&rooms[index], &rooms[index + 1], (rooms_length - index - 1) * sizeof(room));
    rooms_length--;
    rooms = realloc(rooms, rooms_length * sizeof(room));
    save_rooms();
}

override
bool book_room(room r, date date_from, time time_from, date date_to, time time_to) {
    int index = find_room(r.name);
    if (index == -1) return false;

    load_rooms();
    if (!is_room_available(r, date_from, time_from, date_to, time_to)) {
        return false;
    }

    rooms[index].bookings[rooms[index].bookings_length++] = (booking) { date_from, time_from, date_to, time_to };

    save_rooms();
    return true;
}

override
room get_room(int index) {
    return rooms[index];
}

override
bool room_exists(string name) {
    return find_room(name) != -1;
}

override
int get_filtered_rooms_length() {
    return filtered_rooms_length;
}

override
room get_filtered_room(int index) {
    return filtered_rooms[index];
}

override
void cancel_booking(room r, booking b) {
    int index = find_room(r.name);
    if (index == -1) return;

    for (int i = 0; i < rooms[index].bookings_length; i++) {
        if (compare_date_time(b.date_from, b.time_from, rooms[index].bookings[i].date_from, rooms[index].bookings[i].time_from) == 0
                && compare_date_time(b.date_to, b.time_to, rooms[index].bookings[i].date_to, rooms[index].bookings[i].time_to) == 0) {
            memcpy(&rooms[index].bookings[i], &rooms[index].bookings[i + 1], (rooms[index].bookings_length - i - 1) * sizeof(booking));
            rooms[index].bookings_length--;
            rooms[index].bookings = realloc(rooms[index].bookings, rooms[index].bookings_length * sizeof(booking));
            save_rooms();
            return;
        }
    }
}

override
void filter_clear() {
    if (filtered_rooms_length != -1) {
        free(filtered_rooms);
        filtered_rooms = NULL;
        filtered_rooms_length = -1;
    }
}

override
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

override
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

override
void filter_rooms_by_availability(availability_filter filter) {
    if (!init_filter() && filtered_rooms_length == 0) return;
    if (!filter.set) return;
    int new_filtered_rooms_length = 0;
    for (int i = 0; i < filtered_rooms_length; i++) {
        room r = filtered_rooms[i];

        if (is_room_available(r, filter.date_from, filter.time_from, filter.date_to, filter.time_to)) {
            filtered_rooms[new_filtered_rooms_length++] = r;
        }
    }
    filtered_rooms = realloc(filtered_rooms, new_filtered_rooms_length * sizeof(room));;
    filtered_rooms_length = new_filtered_rooms_length;
}*/

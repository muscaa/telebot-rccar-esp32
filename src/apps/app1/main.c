/*
#1. Meeting rooms reservation system

The user can view the available rooms and book a room.
The app allows adding/deleting a room with name and capacity,
displaying all rooms and bookings, searching for a room by name,
capacity and availability, booking the room and canceling the booking.
To book a room, the user must specify the date and time.

- view available rooms
    - book room (date, time)
- add room (name, capacity)
- delete room
- display rooms
    - by name
    - by capacity
    - by availability
- display bookings
    - cancel booking
*/

#include "main.h"

#define TITLE option_title("Meeting rooms reservation system").build()

#define ID_BACK 0

int menu_rooms_view() {
    option options[] = {
        TITLE,
        option_separator()
                .build(),
        option_selection("No filter")
                .build(),
        option_selection("Filter by name")
                .build(),
        option_selection("Filter by capacity")
                .build(),
        option_selection("Filter by availability")
                .build(),
        option_separator()
                .build(),
        option_selection("Back")
                .id(ID_BACK)
                .build(),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);

    switch (opt.id) {
        case ID_BACK: return app1_main();
    }
    return 0;
}

int menu_rooms_add() {
    return 0;
}

#define ID_ROOMS_VIEW 1
#define ID_ROOMS_ADD 2
int menu_rooms() {
    option options[] = {
        TITLE,
        option_separator()
                .build(),
        option_selection("View rooms")
                .id(ID_ROOMS_VIEW)
                .build(),
        option_selection("Add room")
                .id(ID_ROOMS_ADD)
                .build(),
        option_separator()
                .build(),
        option_selection("Back")
                .id(ID_BACK)
                .build(),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);

    switch (opt.id) {
        case ID_BACK: return app1_main();
        case ID_ROOMS_VIEW: return menu_rooms_view();
        case ID_ROOMS_ADD: return menu_rooms_add();
    }
    return 0;
}

int menu_bookings() {
    return 0;
}

#define ID_ROOMS 1
#define ID_BOOKINGS 2
int app1_main() {
    option options[] = {
        TITLE,
        option_separator()
                .build(),
        option_selection("Rooms")
                .id(ID_ROOMS)
                .build(),
        option_selection("Bookings")
                .id(ID_BOOKINGS)
                .build(),
        option_separator()
                .build(),
        option_selection("Back to Main Menu")
                .id(ID_BACK)
                .build(),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);

    switch (opt.id) {
        case ID_BACK: return main_menu();
        case ID_ROOMS: return menu_rooms();
        case ID_BOOKINGS: return menu_bookings();
    }
    return 0;
}
/*
#1. Meeting room reservation

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

#define ID_MAIN_MENU 0
#define ID_ADD_ROOM 1
#define ID_DELETE_ROOM 2

int app1_main() {
    clear_screen();
    
    option options[] = {
        new_option_builder()
                .name("Meeting room reservation")
                .separator()
                .build(),
        new_option_builder()
                .name("")
                .separator()
                .build(),
        new_option_builder()
                .id(ID_ADD_ROOM)
                .name("Add room")
                .build(),
        new_option_builder()
                .id(ID_DELETE_ROOM)
                .name("Delete room")
                .build(),
        new_option_builder()
                .name("")
                .separator()
                .build(),
        new_option_builder()
                .id(ID_MAIN_MENU)
                .name("Back to Main Menu")
                .build(),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);

    switch (opt.id) {
        case ID_MAIN_MENU: return main_menu();
        case ID_ADD_ROOM: return 0;
        case ID_DELETE_ROOM: return 0;
    }

    return 0;
}
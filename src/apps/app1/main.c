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

#include "../../utils/utils.h"
#include "../../menus.h"
#include "rooms.h"

#define TITLE builder_title("Meeting rooms reservation system").build()

int menu_rooms();
    int menu_rooms_view();
        int menu_rooms_view_nofilter();
        int menu_rooms_view_byname();
        int menu_rooms_view_bycapacity();
        int menu_rooms_view_byavailability();
    int menu_rooms_add();
int menu_bookings();

int no_rooms_available() {
    program_action actions[] = {
        new_action("Back", menu_rooms_view),
    };
    int i = 0;
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator().name("No rooms available.").build(),
        SEPARATOR,
        option_selection_action(actions, &i),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}

int menu_rooms_view_nofilter() {
    if (get_rooms_length() == 0) {
        return no_rooms_available();
    }
    program_action actions[] = {
        new_action("Back", menu_rooms_view),
    };
    int i = 0;
    int j = 0;
    option options[get_rooms_length() + 4];
    options[j++] = TITLE;
    options[j++] = SEPARATOR;
    for (; j < get_rooms_length() + 2; j++) {
        room r = get_room(j - 2);
        options[j] = builder_selection(r.name).id(j).build();
    }
    options[j++] = SEPARATOR;
    options[j++] = option_selection_action(actions, &i);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id >= 2) {
        // room settings
        return 0;
    }
    return action_performed(actions, opt);
}

int menu_rooms_view_byname() {
    return 0;
}

int menu_rooms_view_bycapacity() {
    return 0;
}

int menu_rooms_view_byavailability() {
    return 0;
}

int menu_rooms_view() {
    program_action actions[] = {
        new_action("No filter", menu_rooms_view_nofilter),
        new_action("Filter by name", menu_rooms_view_byname),
        new_action("Filter by capacity", menu_rooms_view_bycapacity),
        new_action("Filter by availability", menu_rooms_view_byavailability),
        new_action("Back", menu_rooms),
    };
    int i = 0;
    option options[] = {
        TITLE,
        SEPARATOR,
        option_selection_action(actions, &i),
        option_selection_action(actions, &i),
        option_selection_action(actions, &i),
        option_selection_action(actions, &i),
        SEPARATOR,
        option_selection_action(actions, &i),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}

int menu_rooms_add() {
    add_room("o camera", 87);
    return menu_rooms();
}

int menu_rooms() {
    program_action actions[] = {
        new_action("View rooms", menu_rooms_view),
        new_action("Add room", menu_rooms_add),
        new_action("Back", app1_main),
    };
    int i = 0;
    option options[] = {
        TITLE,
        SEPARATOR,
        option_selection_action(actions, &i),
        option_selection_action(actions, &i),
        SEPARATOR,
        option_selection_action(actions, &i),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}

int menu_bookings() {
    return 0;
}

int app1_main() {
    program_action actions[] = {
        new_action("Rooms", menu_rooms),
        new_action("Bookings", menu_bookings),
        new_action("Back to Main Menu", main_menu),
    };
    int i = 0;
    option options[] = {
        TITLE,
        SEPARATOR,
        option_selection_action(actions, &i),
        option_selection_action(actions, &i),
        SEPARATOR,
        option_selection_action(actions, &i),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}
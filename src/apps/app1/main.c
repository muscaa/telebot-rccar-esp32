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
#define BACK_TO_MAIN_MENU new_action("Back to Main Menu", main_menu)
#define BACK_TO(back_menu) new_action("Back", back_menu)

int menu_rooms();
    int menu_rooms_view();
        int menu_rooms_view_allrooms();
        int menu_rooms_view_filter();
    int menu_rooms_add();
int menu_bookings();

int menu_no_rooms_available() {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                .name("No rooms available.")
                .build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}

int menu_room_info(room room) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                .name(concat("Room name: ", room.name))
                .build(),
            builder_separator()
                .name(concat("Room capacity: ", as_string(room.capacity)))
                .build(),
        SEPARATOR,
        // options
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id >= 2) {
        return menu_room_info(get_room(opt.id - 2));
    }
    return action_performed(actions, opt);
}

void menu_name_filter(name_filter* filter) {
    start_capture();
    int room_name_length = 0;
    char* room_name = malloc(51);
    room_name[0] = '\0';
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == K_ESCAPE) {
            stop_capture();
            return;
        } else if (room_name_length > 0 && capture == K_BACKSPACE) {
            room_name[--room_name_length] = '\0';
            redraw = true;
        } else if (room_name_length < 50) {
            if ((capture >= 'a' && capture <= 'z')
                || (capture >= 'A' && capture <= 'Z')
                || (capture >= '0' && capture <= '9')
                || capture == ' '
                || capture == '-') {
                    room_name[room_name_length++] = capture;
                    room_name[room_name_length] = '\0';
                    redraw = true;
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            println(TITLE.name);
            println("");
            println("(ESC to go back)");
            println("Name filter: %s", room_name);
        }
    }
    if (room_name_length == 0) {
        filter->name = NULL;
    } else {
        filter->name = realloc(room_name, room_name_length + 1);
    }
    stop_capture();
}

void menu_capacity_filter(capacity_filter* filter) {

}

void menu_availability_filter(availability_filter* filter) {
    
}

int menu_rooms_view_allrooms() {
    if (get_rooms_length() == 0) {
        return menu_no_rooms_available();
    }
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[get_rooms_length() + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (; i < get_rooms_length() + 2; i++) {
        room r = get_room(i - 2);
        options[i] = builder_selection(r.name)
                        .id(i)
                        .build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id >= 2) {
        return menu_room_info(get_room(opt.id - 2));
    }
    return action_performed(actions, opt);
}

int menu_rooms_view_filter() {
    name_filter name;
    capacity_filter capacity;
    availability_filter availability;

    while (true) {
        int actions_index = 0;
        program_action actions[] = {
            BACK_TO(menu_rooms_view),
            BACK_TO_MAIN_MENU,
        };
        option options[] = {
            TITLE,
            SEPARATOR,
            builder_selection("Name filter")
                    .id(2)
                    .build(),
            builder_selection("Capacity filter")
                    .id(3)
                    .build(),
            builder_selection("Availability filter")
                    .id(4)
                    .build(),
            SEPARATOR,
            builder_selection("Apply")
                    .id(5)
                    .build(),
            SEPARATOR,
            option_selection_action(actions, &actions_index),
            option_selection_action(actions, &actions_index),
        };
        option opt = vmenu(sizeof(options) / sizeof(option), options);
        if (opt.id == 5) break;
        if (opt.id == 4) {
            menu_availability_filter(&availability);
            continue;
        }
        if (opt.id == 3) {
            menu_capacity_filter(&capacity);
            continue;
        }
        if (opt.id == 2) {
            menu_name_filter(&name);
            continue;
        }
        return action_performed(actions, opt);
    }
    println(name.name);
    pause_console();
    return 0;
}

int menu_rooms_view() {
    int actions_index = 0;
    program_action actions[] = {
        new_action("All rooms", menu_rooms_view_allrooms),
        new_action("Filter", menu_rooms_view_filter),
        BACK_TO(menu_rooms),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}

int menu_rooms_add() {
    start_capture();
    int room_name_length = 0;
    char* room_name = malloc(51);
    room_name[0] = '\0';
    bool redraw = true;
    bool exists = false;
    int capture;
    while ((capture = read_capture()) != K_RETURN || room_name_length == 0 || exists) {
        if (capture == K_ESCAPE) {
            stop_capture();
            return menu_rooms();
        } else if (room_name_length > 0 && capture == K_BACKSPACE) {
            room_name[--room_name_length] = '\0';
            exists = room_exists(room_name);
            redraw = true;
        } else if (room_name_length < 50) {
            if ((capture >= 'a' && capture <= 'z')
                || (capture >= 'A' && capture <= 'Z')
                || (capture >= '0' && capture <= '9')
                || capture == ' '
                || capture == '-') {
                    room_name[room_name_length++] = capture;
                    room_name[room_name_length] = '\0';
                    exists = room_exists(room_name);
                    redraw = true;
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            println(TITLE.name);
            println("");
            println("(ESC to go back)");
            print("Room name (a-zA-Z0-9): ");
            if (exists) {
                push_foreground(COLOR_RED);
            }
            println(room_name);
            if (exists) {
                pop_foreground();
            }
        }
    }
    room_name = realloc(room_name, room_name_length + 1);

    int room_capacity_length = 0;
    char* room_capacity = malloc(7);
    room_capacity[0] = '\0';
    redraw = true;
    while ((capture = read_capture()) != K_RETURN || room_capacity_length == 0) {
        if (capture == K_ESCAPE) {
            stop_capture();
            return menu_rooms();
        } else if (room_capacity_length > 0 && capture == K_BACKSPACE) {
            room_capacity[--room_capacity_length] = '\0';
            redraw = true;
        } else if (room_capacity_length < 6) {
            if (capture >= '0' && capture <= '9') {
                    room_capacity[room_capacity_length++] = capture;
                    room_capacity[room_capacity_length] = '\0';
                    redraw = true;
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            println(TITLE.name);
            println("");
            println("(ESC to go back)");
            println("Room name (a-zA-Z0-9): %s", room_name);
            println("Room capacity (0-9): %s", room_capacity);
        }
    }
    room_capacity = realloc(room_capacity, room_capacity_length + 1);
    stop_capture();

    add_room(room_name, atoi(room_capacity));
    return menu_rooms();
}

int menu_rooms() {
    int actions_index = 0;
    program_action actions[] = {
        new_action("View rooms", menu_rooms_view),
        new_action("Add room", menu_rooms_add),
        BACK_TO(app1_main),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}

int menu_bookings() {
    return 0;
}

int app1_main() {
    load_rooms();
    int actions_index = 0;
    program_action actions[] = {
        new_action("Rooms", menu_rooms),
        new_action("Bookings", menu_bookings),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    return action_performed(actions, opt);
}
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
        int menu_rooms_view_filter();
    int menu_rooms_add();
int menu_bookings();

bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to) {
    start_capture();

    system_date(&date_from->day, &date_from->month, &date_from->year);
    system_time(&time_from->hour, &time_from->minute);

    for (int i = 0; i < 2; i++) {
        date* date = i == 0 ? date_from : date_to;
        time* time = i == 0 ? time_from : time_to;
        if (i == 1) {
            date->day = date_from->day;
            date->month = date_from->month;
            date->year = date_from->year;
            time->hour = time_from->hour;
            time->minute = time_from->minute;
        }

        int current = 0; // 01/01/2024 00:00
        int capture;
        bool redraw = true;
        while ((capture = read_capture()) != K_RETURN) {
            if (capture == K_ESCAPE) {
                stop_capture();
                return false;
            } else if (capture == K_RIGHT) {
                current = (current + 1) % 5;
                redraw = true;
            } else if (capture == K_LEFT) {
                current = (current + 4) % 5;
                redraw = true;
            } else if (capture == K_UP) {
                if (current <= 2) {
                    date_increment(current, date);
                } else {
                    time_increment(current - 3, time);
                }
                redraw = true;
            } else if (capture == K_DOWN) {
                if (current <= 2) {
                    date_decrement(current, date);
                } else {
                    time_decrement(current - 3, time);
                }
                redraw = true;
            }

            if (redraw) {
                redraw = false;

                clear_screen();

                println(TITLE.name);
                println("");
                if (i == 1) {
                    print("From: ");
                    print(as_string_len(date_from->day, 2));
                    print("/");
                    print(as_string_len(date_from->month, 2));
                    print("/");
                    print(as_string(date_from->year));
                    print(" ");
                    print(as_string_len(time_from->hour, 2));
                    print(":");
                    println(as_string_len(time_from->minute, 2));
                }

                print(i == 0 ? "From: " : "To: ");
                push_foreground(current == 0 ? COLOR_BLUE : COLOR_WHITE);
                print(as_string_len(date->day, 2));
                pop_foreground();
                print("/");
                push_foreground(current == 1 ? COLOR_BLUE : COLOR_WHITE);
                print(as_string_len(date->month, 2));
                pop_foreground();
                print("/");
                push_foreground(current == 2 ? COLOR_BLUE : COLOR_WHITE);
                print(as_string(date->year));
                pop_foreground();
                print(" ");
                push_foreground(current == 3 ? COLOR_BLUE : COLOR_WHITE);
                print(as_string_len(time->hour, 2));
                pop_foreground();
                print(":");
                push_foreground(current == 4 ? COLOR_BLUE : COLOR_WHITE);
                println(as_string_len(time->minute, 2));
                pop_foreground();
                println("");
                println("(ESC to go back)");
            }
        }
    }
    stop_capture();
    return true;
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
        builder_separator()
                .name(concat("Room bookings: ", as_string(room.bookings_length)))
                .build(),
        SEPARATOR,
        builder_selection("Delete")
                .id(2)
                .build(),
        builder_selection("Book")
                .id(3)
                .build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id == 2) {
        delete_room(room);
        return menu_rooms_view();
    } else if (opt.id == 3) {
        date date_from;
        time time_from;
        date date_to;
        time time_to;

        if (menu_date_time_picker(&date_from, &time_from, &date_to, &time_to)) {
            book_room(room, date_from, time_from, date_to, time_to);
        }
        
        return menu_rooms_view();
    }
    return action_performed(actions, opt);
}

void menu_name_filter(name_filter* filter) {
    start_capture();
    int room_name_length = 0;
    char* room_name = malloc(51);
    room_name[0] = '\0';
    if (filter->set) {
        strcpy(room_name, filter->name);
        room_name_length = strlen(room_name);
    }
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == K_ESCAPE) {
            free(room_name);
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
            print("Name filter: ");
            push_foreground(COLOR_BLUE);
            println(room_name);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    if (room_name_length == 0) {
        filter->set = false;
        filter->name = NULL;
    } else {
        filter->set = true;
        filter->name = realloc(room_name, room_name_length + 1);
    }
    stop_capture();
}

void menu_capacity_filter(capacity_filter* filter) {
    start_capture();
    int room_capacity_length = 0;
    char* room_capacity = malloc(7);
    room_capacity[0] = '\0';
    if (filter->set) {
        strcpy(room_capacity, as_string(filter->capacity));
        room_capacity_length = strlen(room_capacity);
    }
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == K_ESCAPE) {
            free(room_capacity);
            stop_capture();
            return;
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
            print("Capacity filter: ");
            push_foreground(COLOR_BLUE);
            println(room_capacity);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    if (room_capacity_length == 0) {
        filter->set = false;
        filter->capacity = 0;
        filter->mode = 0;
    } else {
        int current = 0;
        redraw = true;
        while ((capture = read_capture()) != K_RETURN) {
            if (capture == K_ESCAPE) {
                free(room_capacity);
                stop_capture();
                return;
            } else if (capture == K_RIGHT) {
                current = (current + 1) % 3;
                redraw = true;
            } else if (capture == K_LEFT) {
                current = (current + 2) % 3;
                redraw = true;
            }

            if (redraw) {
                redraw = false;

                clear_screen();

                println(TITLE.name);
                println("");
                print("Capacity filter: ");
                push_foreground(COLOR_BLUE);
                println(room_capacity);
                pop_foreground();

                print("Capacity mode: ");
                push_foreground(current == 0 ? COLOR_BLUE : COLOR_WHITE);
                print("Lower");
                pop_foreground();
                print(" ");
                push_foreground(current == 1 ? COLOR_BLUE : COLOR_WHITE);
                print("Equal");
                pop_foreground();
                print(" ");
                push_foreground(current == 2 ? COLOR_BLUE : COLOR_WHITE);
                println("Higher");
                pop_foreground();
                println("");
                println("(ESC to go back)");
            }
        }

        filter->set = true;
        filter->capacity = atoi(room_capacity);
        filter->mode = current;
    }
    free(room_capacity);
    stop_capture();
}

void menu_availability_filter(availability_filter* filter) {
    date date_from;
    time time_from;
    date date_to;
    time time_to;

    if (menu_date_time_picker(&date_from, &time_from, &date_to, &time_to)) {
        filter->set = true;
        filter->date_from = date_from;
        filter->time_from = time_from;
        filter->date_to = date_to;
        filter->time_to = time_to;
    } else {
        filter->set = false;
    }
}

int menu_rooms_view_availablerooms(int rooms_length, room (*get_room)(int)) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[rooms_length + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (; i < rooms_length + 2; i++) {
        room r = get_room(i - 2);
        options[i] = builder_selection(r.name)
                        .id(i)
                        .build();
    }
    if (rooms_length == 0) {
        options[i++] = builder_separator()
                        .name("No rooms available.")
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
    name_filter name = { false };
    capacity_filter capacity = { false };
    availability_filter availability = { false };

    while (true) {
        int actions_index = 0;
        program_action actions[] = {
            BACK_TO(menu_rooms_view),
            BACK_TO_MAIN_MENU,
        };
        option options[] = {
            TITLE,
            SEPARATOR,
            builder_selection(concat("Name filter",
                            name.set ? concat(" (", concat(name.name, ")")) : ""))
                    .id(2)
                    .build(),
            builder_selection(concat("Capacity filter",
                            capacity.set ? concat(capacity.mode == CAPACITY_LOWER ? " (<=" : capacity.mode == CAPACITY_EQUAL ? " (=" : " (>=",
                            concat(as_string(capacity.capacity), ")")) : ""))
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
    filter_clear();
    filter_rooms_by_name(name);
    filter_rooms_by_capacity(capacity);
    filter_rooms_by_availability(availability);
    return menu_rooms_view_availablerooms(get_filtered_rooms_length(), get_filtered_room);
}

int menu_rooms_view() {
    int actions_index = 0;
    program_action actions[] = {
        //new_action("All rooms", menu_rooms_view_allrooms),
        new_action("Filter", menu_rooms_view_filter),
        BACK_TO(menu_rooms),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_selection("All rooms")
                .id(3)
                .build(),
        option_selection_action(actions, &actions_index),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id == 3) {
        return menu_rooms_view_availablerooms(get_rooms_length(), get_room);
    }
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
            print("Room name: ");
            push_foreground(exists ? COLOR_RED : COLOR_BLUE);
            println(room_name);
            pop_foreground();
            println("");
            println("(ESC to go back)");
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
            print("Room name: ");
            push_foreground(COLOR_BLUE);
            println(room_name);
            pop_foreground();
            print("Room capacity: ");
            push_foreground(COLOR_BLUE);
            println(room_capacity);
            pop_foreground();
            println("");
            println("(ESC to go back)");
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
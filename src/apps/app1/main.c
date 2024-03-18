/*
#1. Meeting rooms reservation system

The user can view the available rooms and book a room.
The app allows adding/deleting a room with name and capacity,
displaying all rooms and bookings, searching for a room by name,
capacity and availability, booking the room and canceling the booking.
To book a room, the user must specify the date and time.
*/

#include "main.h"

#include "../../menus.h"
#include "rooms.h"

#define TITLE builder_title("Meeting rooms reservation system")->build()
#define BACK_TO_MAIN_MENU new_action("Back to Main Menu", main_menu)
#define BACK_TO(back_menu) new_action("Back", back_menu)

/*private int menu_rooms();
    private int menu_rooms_view();
        private int menu_rooms_view_availablerooms(int rooms_length, room (*get_room)(int));
            private int menu_room_info(room room);
                private int menu_room_bookings(room room, int (*back)());
        private int menu_rooms_view_filter();
            private void menu_name_filter(name_filter* filter);
            private void menu_capacity_filter(capacity_filter* filter);
            private void menu_availability_filter(availability_filter* filter);
                private bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to);
    private int menu_rooms_add();
private int menu_bookings();
    private int menu_booking_info(room room, booking booking);

private int menu_booking_info(room room, booking booking) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                ->name(format("Booking from: %02d/%02d/%04d %02d:%02d",
                        booking.date_from.day, booking.date_from.month, booking.date_from.year, booking.time_from.hour, booking.time_from.minute))
                ->build(),
        builder_separator()
                ->name(format("Booking to: %02d/%02d/%04d %02d:%02d",
                        booking.date_to.day, booking.date_to.month, booking.date_to.year, booking.time_to.hour, booking.time_to.minute))
                ->build(),
        SEPARATOR,
        builder_selection("Cancel")
                ->id(2)
                ->build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id == 2) {
        cancel_booking(room, booking);
        return menu_rooms_view();
    }
    return action_performed(actions, opt);
}

private bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to) {
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

                println(TITLE->name);
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

private int menu_room_bookings(room room, int (*back)()) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(back),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[room.bookings_length + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (; i < room.bookings_length + 2; i++) {
        booking b = room.bookings[i - 2];
        options[i] = builder_selection(format("(%02d/%02d/%04d %02d:%02d - %02d/%02d/%04d %02d:%02d)",
                                b.date_from.day, b.date_from.month, b.date_from.year, b.time_from.hour, b.time_from.minute,
                                b.date_to.day, b.date_to.month, b.date_to.year, b.time_to.hour, b.time_to.minute))
                        ->id(i)
                        ->build();
    }
    if (room.bookings_length == 0) {
        options[i++] = builder_separator()
                        ->name("No bookings.")
                        ->build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id >= 2) {
        return menu_booking_info(room, room.bookings[opt->id - 2]);
    }
    return action_performed(actions, opt);
}

private int menu_room_info(room room) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                ->name(format("Room name: %s", room.name))
                ->build(),
        builder_separator()
                ->name(format("Room capacity: %d", room.capacity))
                ->build(),
        SEPARATOR,
        builder_selection(format("Bookings (%d)", room.bookings_length))
                ->id(2)
                ->build(),
        builder_selection("Book")
                ->id(3)
                ->build(),
        builder_selection("Delete")
                ->id(4)
                ->build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id == 2) {
        return menu_room_bookings(room, menu_rooms_view);
    } else if (opt->id == 3) {
        date date_from;
        time time_from;
        date date_to;
        time time_to;

        if (menu_date_time_picker(&date_from, &time_from, &date_to, &time_to)) {
            book_room(room, date_from, time_from, date_to, time_to);
        }
        
        return menu_rooms_view();
    } else if (opt->id == 4) {
        delete_room(room);
        return menu_rooms_view();
    }
    return action_performed(actions, opt);
}

private void draw_name_filter(dialog_input_info info) {
    println(TITLE->name);
    println("");
    print("Name filter: ");
    push_foreground(COLOR_BLUE);
    println(info.result);
    pop_foreground();
    println("");
    println("(ESC to go back)");
}

private void menu_name_filter(name_filter* filter) {
    dialog_input name_filter_di = new_dialog_input_builder()
                    .draw(draw_name_filter)
                    .value(filter->set ? filter->name : NULL)
                    .allow_empty()
                    .accepts("az|AZ|09| |-")
                    .max_length(50)
                    .build();
    string room_name = dialog_input_string(name_filter_di, NULL);
    if (room_name == NULL) return;

    if (strlen(room_name) == 0) {
        filter->set = false;
        filter->name = NULL;
    } else {
        filter->set = true;
        filter->name = room_name;
    }
}

private void draw_capacity_filter(dialog_input_info info) {
    println(TITLE->name);
    println("");
    print("Capacity filter: ");
    push_foreground(COLOR_BLUE);
    println(info.result);
    pop_foreground();
    println("");
    println("(ESC to go back)");
}

private void menu_capacity_filter(capacity_filter* filter) {
    dialog_input capacity_filter_di = new_dialog_input_builder()
                    .draw(draw_capacity_filter)
                    .value(filter->set ? as_string(filter->capacity) : NULL)
                    .allow_empty()
                    .accepts("09")
                    .max_length(6)
                    .build();
    string room_capacity = dialog_input_string(capacity_filter_di, NULL);
    if (room_capacity == NULL) return;
    int room_capacity_length = strlen(room_capacity);

    start_capture();
    if (room_capacity_length == 0) {
        filter->set = false;
        filter->capacity = 0;
        filter->mode = 0;
    } else {
        int current = 0;
        int capture;
        bool redraw = true;
        while ((capture = read_capture()) != K_RETURN) {
            if (capture == K_ESCAPE) {
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

                println(TITLE->name);
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
    stop_capture();
}

private void menu_availability_filter(availability_filter* filter) {
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

private int menu_rooms_view_availablerooms(int rooms_length, room (*get_room)(int)) {
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
                        ->id(i)
                        ->build();
    }
    if (rooms_length == 0) {
        options[i++] = builder_separator()
                        ->name("No rooms available.")
                        ->build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id >= 2) {
        return menu_room_info(get_room(opt->id - 2));
    }
    return action_performed(actions, opt);
}

private int menu_rooms_view_filter() {
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
            builder_selection(format("Name filter %s", name.set ? format("(%s)", name.name) : ""))
                    ->id(2)
                    ->build(),
            builder_selection(format("Capacity filter %s", capacity.set ? format("(%s %d)",
                                    capacity.mode == CAPACITY_LOWER ? "<=" :
                                    capacity.mode == CAPACITY_EQUAL ? "=" :
                                    capacity.mode == CAPACITY_HIGHER ? ">=" : "",
                                    capacity.capacity) : ""))
                    ->id(3)
                    ->build(),
            builder_selection(format("Availability filter %s", availability.set ? format("(%02d/%02d/%04d %02d:%02d - %02d/%02d/%04d %02d:%02d)",
                                availability.date_from.day, availability.date_from.month, availability.date_from.year, availability.time_from.hour, availability.time_from.minute,
                                availability.date_to.day, availability.date_to.month, availability.date_to.year, availability.time_to.hour, availability.time_to.minute) : ""))
                    ->id(4)
                    ->build(),
            SEPARATOR,
            builder_selection("Apply")
                    ->id(5)
                    ->build(),
            SEPARATOR,
            option_selection_action(actions, &actions_index),
            option_selection_action(actions, &actions_index),
        };
        option opt = vmenu(sizeof(options) / sizeof(option), options);
        if (opt->id == 5) break;
        if (opt->id == 4) {
            menu_availability_filter(&availability);
            continue;
        }
        if (opt->id == 3) {
            menu_capacity_filter(&capacity);
            continue;
        }
        if (opt->id == 2) {
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

private int menu_rooms_view() {
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
                ->id(3)
                ->build(),
        option_selection_action(actions, &actions_index),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id == 3) {
        return menu_rooms_view_availablerooms(get_rooms_length(), get_room);
    }
    return action_performed(actions, opt);
}

private void draw_room_name(dialog_input_info info) {
    println(TITLE->name);
    println("");
    print("Room name: ");
    push_foreground(info.exists ? COLOR_RED : COLOR_BLUE);
    println(info.result);
    pop_foreground();
    println("");
    println("(ESC to go back)");
}

private void draw_room_capacity(dialog_input_info info) {
    string room_name = info.additional;
    println(TITLE->name);
    println("");
    print("Room name: ");
    push_foreground(COLOR_BLUE);
    println(room_name);
    pop_foreground();
    print("Room capacity: ");
    push_foreground(COLOR_BLUE);
    println(info.result);
    pop_foreground();
    println("");
    println("(ESC to go back)");
}

private int menu_rooms_add() {
    dialog_input room_name_di = new_dialog_input_builder()
                    .draw(draw_room_name)
                    .exists(room_exists)
                    .accepts("az|AZ|09| |-")
                    .max_length(50)
                    .build();
    string room_name = dialog_input_string(room_name_di, NULL);
    if (room_name == NULL) return menu_rooms();

    dialog_input room_capacity_di = new_dialog_input_builder()
                    .draw(draw_room_capacity)
                    .accepts("09")
                    .max_length(6)
                    .build();
    string room_capacity = dialog_input_string(room_capacity_di, room_name);
    if (room_capacity == NULL) return menu_rooms();
    
    add_room(room_name, atoi(room_capacity));
    return menu_rooms();
}

private int menu_rooms() {
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

private int menu_bookings() {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[get_rooms_length() + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (int j = 0; j < get_rooms_length(); j++) {
        room r = get_room(j);
        if (r.bookings_length == 0) continue;

        options[i++] = builder_selection(format("%s (%d bookings)", r.name, r.bookings_length))
                        ->id(j + 2)
                        ->build();
    }
    if (get_rooms_length() == 0) {
        options[i++] = builder_separator()
                        ->name("No bookings available.")
                        ->build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(i, options);
    if (opt->id >= 2) {
        return menu_room_bookings(get_room(opt->id - 2), app1_main);
    }
    return action_performed(actions, opt);
}*/

override
int app1_main() {
    /*load_rooms();
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
    return action_performed(actions, opt);*/
    return 0;
}

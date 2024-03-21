#include "appmenus.h"

override
menu rooms_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_ROOMS, "Rooms"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_BOOKINGS, "Bookings"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_ROOMS_MENU_VIEW, "View rooms"));
    mcall(options, add, SELECTION(ID_ROOMS_MENU_ADD, "Add room"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_bookings_menu() {
    option_array options = new(option_array);
    for (int i = 0; i < _get_rooms_length(); i++) {
        room r = _get_room(i);
        if (r.bookings_length == 0) continue;

        mcall(options, add, SELECTION(i, format("%s (%d bookings)", r.name, r.bookings_length)));
    }
    if (_get_rooms_length() == 0) {
        mcall(options, add, option_separator()
                        ->name("No bookings available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_VIEW_MENU_ALL, "All rooms"));
    mcall(options, add, SELECTION(ID_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_add_menu() {
    return NULL;
    /*
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
    */
}

override
menu rooms_available_menu(int rooms_length, room function(get_room, int index)) {
    option_array options = new(option_array);
    for (int i = 0; i < rooms_length; i++) {
        room r = get_room(i);

        mcall(options, add, SELECTION(i, r.name));
    }
    if (rooms_length == 0) {
        mcall(options, add, option_separator()
                        ->name("No rooms available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_filter_menu() { // room filters as args, then when applying, go back 2 screens, show this one with modified filters
    name_filter name = { false };
    capacity_filter capacity = { false };
    availability_filter availability = { false };
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_FILTER_MENU_NAME, format("Name filter %s", name.set ? format("(%s)", name.name) : "")));
    mcall(options, add, SELECTION(ID_FILTER_MENU_CAPACITY, format("Capacity filter %s", capacity.set ? format("(%s %d)",
                                    capacity.mode == CAPACITY_LOWER ? "<=" :
                                    capacity.mode == CAPACITY_EQUAL ? "=" :
                                    capacity.mode == CAPACITY_HIGHER ? ">=" : "", capacity.capacity) : "")));
    mcall(options, add, SELECTION(ID_FILTER_MENU_AVAILABILITY, format("Availability filter %s", availability.set ? format("(%02d/%02d/%04d %02d:%02d - %02d/%02d/%04d %02d:%02d)",
                                availability.date_from.day, availability.date_from.month, availability.date_from.year, availability.time_from.hour, availability.time_from.minute,
                                availability.date_to.day, availability.date_to.month, availability.date_to.year, availability.time_to.hour, availability.time_to.minute) : "")));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
    /*
    filter_clear();
    filter_rooms_by_name(name);
    filter_rooms_by_capacity(capacity);
    filter_rooms_by_availability(availability);
    return menu_rooms_view_availablerooms(get_filtered_rooms_length(), get_filtered_room);
    */
}

override
menu rooms_filter_name_menu() {
    return NULL;
    /*
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
    */
}

override
menu rooms_filter_capacity_menu() {
    return NULL;
    /*
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
    */
}

override
menu rooms_filter_availability_menu() {
    return NULL;
    /*
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
    */
}

override
menu rooms_room_info_menu(room r) {
    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->name(format("Room name: %s", r.name))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Room capacity: %d", r.capacity))
                    ->build());
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_ROOM_INFO_MENU_BOOKINGS, format("Bookings (%d)", r.bookings_length)));
    mcall(options, add, SELECTION(ID_ROOM_INFO_MENU_BOOK, format("Book", r.bookings_length)));
    mcall(options, add, SELECTION(ID_ROOM_INFO_MENU_DELETE, format("Delete", r.bookings_length)));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
    /*
    if (opt->id == 3) {
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
    */
}

override
menu rooms_room_bookings_menu(room r) {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_ROOM_INFO_MENU_BOOKINGS, format("Bookings (%d)", r.bookings_length)));
    mcall(options, add, SELECTION(ID_ROOM_INFO_MENU_BOOK, format("Book", r.bookings_length)));
    mcall(options, add, SELECTION(ID_ROOM_INFO_MENU_DELETE, format("Delete", r.bookings_length)));
    for (int i = 0; i < r.bookings_length; i++) {
        booking b = r.bookings[i];

        mcall(options, add, SELECTION(i, format("(%02d/%02d/%04d %02d:%02d - %02d/%02d/%04d %02d:%02d)",
                                b.date_from.day, b.date_from.month, b.date_from.year, b.time_from.hour, b.time_from.minute,
                                b.date_to.day, b.date_to.month, b.date_to.year, b.time_to.hour, b.time_to.minute)));
    }
    if (r.bookings_length == 0) {
        mcall(options, add, option_separator()
                        ->name("No bookings available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_booking_info_menu(room r, booking b) {
    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->name(format("Booking from: %02d/%02d/%04d %02d:%02d",
                        b.date_from.day, b.date_from.month, b.date_from.year, b.time_from.hour, b.time_from.minute))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Booking to: %02d/%02d/%04d %02d:%02d",
                        b.date_to.day, b.date_to.month, b.date_to.year, b.time_to.hour, b.time_to.minute))
                    ->build());
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_BOOKING_INFO_MENU_CANCEL, "Cancel"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

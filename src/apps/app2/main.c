/*
#2. Library books tracking system

The system allows to store the data of the books in a library.
The user can add books by specifying title, author, types, search
and display books by title, author and availability, borrow
books for a number of days and return borrowed books.
*/

#include "main.h"

#include "../../utils/utils.h"
#include "../../menus.h"
#include "books.h"

#define TITLE builder_title("Library books tracking system").build()
#define BACK_TO_MAIN_MENU new_action("Back to Main Menu", main_menu)
#define BACK_TO(back_menu) new_action("Back", back_menu)

int menu_books();
    int menu_books_view();
        int menu_books_view_availablebooks(int books_length, book (*get_book)(int));
            int menu_book_info(book book);
                //int menu_book_bookings(book book, int (*back)());
        int menu_books_view_filter();
            //void menu_name_filter(name_filter* filter);
            //void menu_capacity_filter(capacity_filter* filter);
            //void menu_availability_filter(availability_filter* filter);
                //bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to);
    int menu_books_add();
int menu_bookingss();
    //int menu_booking_info(book book, booking booking);

/*int menu_booking_info(book book, booking booking) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_books_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                .name(format("Booking from: %02d/%02d/%04d %02d:%02d",
                        booking.date_from.day, booking.date_from.month, booking.date_from.year, booking.time_from.hour, booking.time_from.minute))
                .build(),
        builder_separator()
                .name(format("Booking to: %02d/%02d/%04d %02d:%02d",
                        booking.date_to.day, booking.date_to.month, booking.date_to.year, booking.time_to.hour, booking.time_to.minute))
                .build(),
        SEPARATOR,
        builder_selection("Cancel")
                .id(2)
                .build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id == 2) {
        cancel_booking(book, booking);
        return menu_books_view();
    }
    return action_performed(actions, opt);
}*/

/*bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to) {
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
}*/

/*int menu_book_bookings(book book, int (*back)()) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(back),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[book.bookings_length + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (; i < book.bookings_length + 2; i++) {
        booking b = book.bookings[i - 2];
        options[i] = builder_selection(format("(%02d/%02d/%04d %02d:%02d - %02d/%02d/%04d %02d:%02d)",
                                b.date_from.day, b.date_from.month, b.date_from.year, b.time_from.hour, b.time_from.minute,
                                b.date_to.day, b.date_to.month, b.date_to.year, b.time_to.hour, b.time_to.minute))
                        .id(i)
                        .build();
    }
    if (book.bookings_length == 0) {
        options[i++] = builder_separator()
                        .name("No bookings.")
                        .build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id >= 2) {
        return menu_booking_info(book, book.bookings[opt.id - 2]);
    }
    return action_performed(actions, opt);
}*/

int menu_book_info(book book) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_books_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                .name(format("Book title: %s", book.title))
                .build(),
        builder_separator()
                .name(format("Book author: %s", book.author))
                .build(),
        SEPARATOR,
        builder_selection("Book")
                .id(3)
                .build(),
        builder_selection("Delete")
                .id(4)
                .build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id == 2) {
        //return menu_book_bookings(book, menu_books_view);
        return 0;
    } else if (opt.id == 3) {
        date date_from;
        time time_from;
        date date_to;
        time time_to;

        /*if (menu_date_time_picker(&date_from, &time_from, &date_to, &time_to)) {
            book_book(book, date_from, time_from, date_to, time_to);
        }*/
        
        return menu_books_view();
    } else if (opt.id == 4) {
        delete_book(book);
        return menu_books_view();
    }
    return action_performed(actions, opt);
}

/*void menu_name_filter(name_filter* filter) {
    start_capture();
    int book_name_length = 0;
    char* book_name = malloc(51);
    book_name[0] = '\0';
    if (filter->set) {
        strcpy(book_name, filter->name);
        book_name_length = strlen(book_name);
    }
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == K_ESCAPE) {
            free(book_name);
            stop_capture();
            return;
        } else if (book_name_length > 0 && capture == K_BACKSPACE) {
            book_name[--book_name_length] = '\0';
            redraw = true;
        } else if (book_name_length < 50) {
            if ((capture >= 'a' && capture <= 'z')
                || (capture >= 'A' && capture <= 'Z')
                || (capture >= '0' && capture <= '9')
                || capture == ' '
                || capture == '-') {
                    book_name[book_name_length++] = capture;
                    book_name[book_name_length] = '\0';
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
            println(book_name);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    if (book_name_length == 0) {
        filter->set = false;
        filter->name = NULL;
    } else {
        filter->set = true;
        filter->name = realloc(book_name, book_name_length + 1);
    }
    stop_capture();
}*/

/*void menu_capacity_filter(capacity_filter* filter) {
    start_capture();
    int book_capacity_length = 0;
    char* book_capacity = malloc(7);
    book_capacity[0] = '\0';
    if (filter->set) {
        strcpy(book_capacity, as_string(filter->capacity));
        book_capacity_length = strlen(book_capacity);
    }
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == K_ESCAPE) {
            free(book_capacity);
            stop_capture();
            return;
        } else if (book_capacity_length > 0 && capture == K_BACKSPACE) {
            book_capacity[--book_capacity_length] = '\0';
            redraw = true;
        } else if (book_capacity_length < 6) {
            if (capture >= '0' && capture <= '9') {
                    book_capacity[book_capacity_length++] = capture;
                    book_capacity[book_capacity_length] = '\0';
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
            println(book_capacity);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    if (book_capacity_length == 0) {
        filter->set = false;
        filter->capacity = 0;
        filter->mode = 0;
    } else {
        int current = 0;
        redraw = true;
        while ((capture = read_capture()) != K_RETURN) {
            if (capture == K_ESCAPE) {
                free(book_capacity);
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
                println(book_capacity);
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
        filter->capacity = atoi(book_capacity);
        filter->mode = current;
    }
    free(book_capacity);
    stop_capture();
}*/

/*void menu_availability_filter(availability_filter* filter) {
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
}*/

int menu_books_view_availablebooks(int books_length, book (*get_book)(int)) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_books_view),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[books_length + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (; i < books_length + 2; i++) {
        book b = get_book(i - 2);
        options[i] = builder_selection(format("%s (%s)", b.title, b.author))
                        .id(i)
                        .build();
    }
    if (books_length == 0) {
        options[i++] = builder_separator()
                        .name("No books available.")
                        .build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id >= 2) {
        return menu_book_info(get_book(opt.id - 2));
    }
    return action_performed(actions, opt);
}

int menu_books_view_filter() {
    /*name_filter name = { false };
    capacity_filter capacity = { false };
    availability_filter availability = { false };

    while (true) {
        int actions_index = 0;
        program_action actions[] = {
            BACK_TO(menu_books_view),
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
    filter_books_by_name(name);
    filter_books_by_capacity(capacity);
    filter_books_by_availability(availability);
    return menu_books_view_availablebooks(get_filtered_books_length(), get_filtered_book);*/
    return 0;
}

int menu_books_view() {
    int actions_index = 0;
    program_action actions[] = {
        new_action("Filter", menu_books_view_filter),
        BACK_TO(menu_books),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_selection("All books")
                .id(3)
                .build(),
        option_selection_action(actions, &actions_index),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt.id == 3) {
        return menu_books_view_availablebooks(get_books_length(), get_book);
    }
    return action_performed(actions, opt);
}

int menu_books_add() {
    start_capture();
    int book_title_length = 0;
    char* book_title = malloc(51);
    book_title[0] = '\0';
    bool redraw = true;
    bool exists = false;
    int capture;
    while ((capture = read_capture()) != K_RETURN || book_title_length == 0 || exists) {
        if (capture == K_ESCAPE) {
            stop_capture();
            return menu_books();
        } else if (book_title_length > 0 && capture == K_BACKSPACE) {
            book_title[--book_title_length] = '\0';
            exists = book_exists(book_title);
            redraw = true;
        } else if (book_title_length < 50) {
            if ((capture >= 'a' && capture <= 'z')
                || (capture >= 'A' && capture <= 'Z')
                || (capture >= '0' && capture <= '9')
                || capture == ' '
                || capture == '-') {
                    book_title[book_title_length++] = capture;
                    book_title[book_title_length] = '\0';
                    exists = book_exists(book_title);
                    redraw = true;
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            println(TITLE.name);
            println("");
            print("Book title: ");
            push_foreground(exists ? COLOR_RED : COLOR_BLUE);
            println(book_title);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    book_title = realloc(book_title, book_title_length + 1);

    int book_capacity_length = 0;
    char* book_capacity = malloc(7);
    book_capacity[0] = '\0';
    redraw = true;
    while ((capture = read_capture()) != K_RETURN || book_capacity_length == 0) {
        if (capture == K_ESCAPE) {
            stop_capture();
            return menu_books();
        } else if (book_capacity_length > 0 && capture == K_BACKSPACE) {
            book_capacity[--book_capacity_length] = '\0';
            redraw = true;
        } else if (book_capacity_length < 6) {
            if (capture >= '0' && capture <= '9') {
                    book_capacity[book_capacity_length++] = capture;
                    book_capacity[book_capacity_length] = '\0';
                    redraw = true;
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            println(TITLE.name);
            println("");
            print("Book title: ");
            push_foreground(COLOR_BLUE);
            println(book_title);
            pop_foreground();
            print("Book capacity: ");
            push_foreground(COLOR_BLUE);
            println(book_capacity);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    book_capacity = realloc(book_capacity, book_capacity_length + 1);
    stop_capture();

    add_book(book_title, atoi(book_capacity));
    return menu_books();
}

int menu_books() {
    int actions_index = 0;
    program_action actions[] = {
        new_action("View books", menu_books_view),
        new_action("Add book", menu_books_add),
        BACK_TO(app2_main),
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

int menu_bookingss() {
    /*int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_books_view),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[get_books_length() + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (int j = 0; j < get_books_length(); j++) {
        book r = get_book(j);
        if (r.bookings_length == 0) continue;

        options[i++] = builder_selection(format("%s (%d bookings)", r.name, r.bookings_length))
                        .id(j + 2)
                        .build();
    }
    if (get_books_length() == 0) {
        options[i++] = builder_separator()
                        .name("No bookings available.")
                        .build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(i, options);
    if (opt.id >= 2) {
        return menu_book_bookings(get_book(opt.id - 2), app1_main);
    }
    return action_performed(actions, opt);*/
    return 0;
}

int app2_main() {
    load_books();
    int actions_index = 0;
    program_action actions[] = {
        new_action("Books", menu_books),
        new_action("Bookings", menu_bookingss),
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
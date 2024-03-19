/*
#2. Library books tracking system

The system allows to store the data of the books in a library.
The user can add books by specifying title, author, types, search
and display books by title, author and availability, borrow
books for a number of days and return borrowed books.

- view books
    - all books
    - by title
    - by author
    - by type
    - by availability
- view borrowed books
    - return book
- add book
    - title
    - author
    - types
*/

#include "appmain.h"

#include "../../menus.h"
#include "books.h"

#define TITLE builder_title("Library books tracking system").build()
#define BACK_TO_MAIN_MENU new_action("Back to Main Menu", main_menu)
#define BACK_TO(back_menu) new_action("Back", back_menu)

/*private int menu_books();
    private int menu_books_view();
        private int menu_books_view_availablebooks(int books_length, book (*get_book)(int));
            private int menu_book_info(book book);
                //int menu_book_bookings(book book, int (*back)());
        private int menu_books_view_filter();
            //void menu_name_filter(name_filter* filter);
            //void menu_capacity_filter(capacity_filter* filter);
            //void menu_availability_filter(availability_filter* filter);
                //bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to);
    private int menu_books_add();
private int menu_bookingss();
    //int menu_booking_info(book book, booking booking);

private int menu_book_info(book book) {
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
        
        return menu_books_view();
    } else if (opt.id == 4) {
        delete_book(book);
        return menu_books_view();
    }
    return action_performed(actions, opt);
}

private int menu_books_view_availablebooks(int books_length, book (*get_book)(int)) {
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

private int menu_books_view_filter() {
    return 0;
}

private int menu_books_view() {
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

private int menu_books_add() {
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

    //add_book(book_title, atoi(book_capacity));
    return menu_books();
}

private int menu_books() {
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

private int menu_bookingss() {
    return 0;
}*/

override
int app2_main() {
    /*load_books();
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
    return action_performed(actions, opt);*/
    return 0;
}

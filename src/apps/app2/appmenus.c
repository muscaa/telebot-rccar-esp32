#include "appmenus.h"

override
menu books_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_BOOKS, "Books"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_BORROWED, "Borrowed books"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu books_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_BOOKS_MENU_VIEW, "View books"));
    mcall(options, add, SELECTION(ID_BOOKS_MENU_ADD, "Add book"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu books_borrowed_menu() {
    return NULL;
}

override
menu books_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_VIEW_MENU_ALL, "All books"));
    mcall(options, add, SELECTION(ID_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu books_add_menu() {
    return NULL;
}

override
menu books_available_menu() {
    return NULL;
}

override
menu books_filter_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_FILTER_MENU_TITLE, "By title"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_AUTHOR, "By author"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_TYPE, "By type"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_LOCATION, "By location"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_AVAILABILITY, "By availability"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu books_filter_title_menu() {
    return NULL;
}

override
menu books_filter_author_menu() {
    return NULL;
}

override
menu books_filter_type_menu() {
    return NULL;
}

override
menu books_filter_location_menu() {
    return NULL;
}

override
menu books_filter_availability_menu() {
    return NULL;
}

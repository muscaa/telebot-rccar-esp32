#include "appmenus.h"

override
menu app4_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_PRODUCTS, "Products"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_RESERVATIONS, "Reservations"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_PRODUCTS_MENU_VIEW, "View products"));
    mcall(options, add, SELECTION(ID_PRODUCTS_MENU_ADD, "Add product"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_reservations_menu() {
    return NULL;
}

override
menu products_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_VIEW_MENU_ALL, "All products"));
    mcall(options, add, SELECTION(ID_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_add_menu() {
    return NULL;
}

override
menu products_available_menu() {
    return NULL;
}

override
menu products_filter_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_FILTER_MENU_NAME, "Name filter"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_LOCATION, "Location filter"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_AVAILABILITY, "Availability filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_filter_name_menu() {
    return NULL;
}

override
menu products_filter_location_menu() {
    return NULL;
}

override
menu products_filter_availability_menu() {
    return NULL;
}

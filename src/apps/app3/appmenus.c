#include "appmenus.h"

override
menu bikes_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_BIKES, "Bikes"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_RESERVATIONS, "Reservations"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu bikes_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_BIKES_MENU_VIEW, "View bikes"));
    mcall(options, add, SELECTION(ID_BIKES_MENU_ADD, "Add bike"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu bikes_reservations_menu() {
    return NULL;
}

override
menu bikes_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_VIEW_MENU_ALL, "All bikes"));
    mcall(options, add, SELECTION(ID_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu bikes_add_menu() {
    return NULL;
}

override
menu bikes_available_menu() {
    return NULL;
}

override
menu bikes_filter_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_FILTER_MENU_TYPE, "Type filter"));
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
menu bikes_filter_type_menu() {
    return NULL;
}

override
menu bikes_filter_location_menu() {
    return NULL;
}

override
menu bikes_filter_availability_menu() {
    return NULL;
}

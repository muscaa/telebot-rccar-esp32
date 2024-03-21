#include "appmenus.h"

override
menu trains_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_TRAINS, "Trains"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_WAGONS, "Wagons"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_TRAINS_MENU_VIEW, "View trains"));
    mcall(options, add, SELECTION(ID_TRAINS_MENU_ADD, "Add train"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_TRAINS_VIEW_MENU_ALL, "View all"));
    mcall(options, add, SELECTION(ID_TRAINS_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_add_menu() {
    return NULL;
}

override
menu trains_available_menu() {
    return NULL;
}

override
menu trains_filter_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_TRAINS_FILTER_MENU_ID, "Filter ID"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_TRAINS_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_filter_id_menu() {
    return NULL;
}

override
menu wagons_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_WAGONS_MENU_VIEW, "View wagons"));
    mcall(options, add, SELECTION(ID_WAGONS_MENU_ADD, "Add wagon"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_WAGONS_VIEW_MENU_ALL, "View all"));
    mcall(options, add, SELECTION(ID_WAGONS_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_add_menu() {
    return NULL;
}

override
menu wagons_available_menu() {
    return NULL;
}

override
menu wagons_filter_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_WAGONS_FILTER_MENU_ID, "Filter ID"));
    mcall(options, add, SELECTION(ID_WAGONS_FILTER_MENU_TYPE, "Filter type"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_WAGONS_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_filter_id_menu() {
    return NULL;
}

override
menu wagons_filter_type_menu() {
    return NULL;
}

#pragma once

#include "../app.h"

enum Menus {
    bikes_main, // bikes_main_menu
    bikes, // bikes_menu
    bikes_reservations, // bikes_reservations_menu
    bikes_view, // bikes_view_menu
    bikes_add, // bikes_add_menu
    bikes_all, // bikes_available_menu
    bikes_filter, // bikes_filter_menu
    bikes_filter_type, // bikes_filter_type_menu
    bikes_filter_location, // bikes_filter_location_menu
    bikes_filter_availability, // bikes_filter_availability_menu
};

#define ID_MAIN_MENU_BIKES 0
#define ID_MAIN_MENU_RESERVATIONS 1
menu bikes_main_menu();

#define ID_BIKES_MENU_VIEW 0
#define ID_BIKES_MENU_ADD 1
menu bikes_menu();

menu bikes_reservations_menu();

#define ID_VIEW_MENU_ALL 0
#define ID_VIEW_MENU_FILTER 1
menu bikes_view_menu();

menu bikes_add_menu();

menu bikes_available_menu();

#define ID_FILTER_MENU_TYPE 0
#define ID_FILTER_MENU_LOCATION 1
#define ID_FILTER_MENU_AVAILABILITY 2
#define ID_FILTER_MENU_APPLY 3
menu bikes_filter_menu();

menu bikes_filter_type_menu();

menu bikes_filter_location_menu();

menu bikes_filter_availability_menu();

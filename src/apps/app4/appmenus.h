#pragma once

#include "../app.h"

enum Menus {
    products_main, // products_main_menu
    products, // products_menu
    products_reservations, // products_reservations_menu
    products_view, // products_view_menu
    products_add, // products_add_menu
    products_all, // products_available_menu
    products_filter, // products_filter_menu
    products_filter_name, // products_filter_name_menu
    products_filter_location, // products_filter_location_menu
    products_filter_availability, // products_filter_availability_menu
};

#define ID_MAIN_MENU_PRODUCTS 0
#define ID_MAIN_MENU_RESERVATIONS 1
menu products_main_menu();

#define ID_PRODUCTS_MENU_VIEW 0
#define ID_PRODUCTS_MENU_ADD 1
menu products_menu();

menu products_reservations_menu();

#define ID_VIEW_MENU_ALL 0
#define ID_VIEW_MENU_FILTER 1
menu products_view_menu();

menu products_add_menu();

menu products_available_menu();

#define ID_FILTER_MENU_NAME 0
#define ID_FILTER_MENU_LOCATION 1
#define ID_FILTER_MENU_AVAILABILITY 2
#define ID_FILTER_MENU_APPLY 3
menu products_filter_menu();

menu products_filter_name_menu();

menu products_filter_location_menu();

menu products_filter_availability_menu();

#pragma once

#include "../app.h"
#include "products.h"

enum Menus {
    app4, // app4_menu
    products_main, // products_menu
    products_reservations, // products_reservations_menu
    products_view, // products_view_menu
    products_available, // products_available_menu
    products_filter, // products_filter_menu
    products_info, // products_info_menu
};

#define ID_MAIN_MENU_PRODUCTS 0
#define ID_MAIN_MENU_RESERVATIONS 1
menu app4_menu();

#define ID_PRODUCTS_MENU_VIEW 0
#define ID_PRODUCTS_MENU_ADD 1
menu products_main_menu();

menu products_reservations_menu();

#define ID_VIEW_MENU_ALL 0
#define ID_VIEW_MENU_FILTER 1
menu products_view_menu();

void products_add_screen();

menu products_available_menu(product_array available);

#define ID_FILTER_MENU_NAME 0
#define ID_FILTER_MENU_TYPE 1
#define ID_FILTER_MENU_LOCATION 2
#define ID_FILTER_MENU_QUANTITY 3
#define ID_FILTER_MENU_APPLY 4
menu products_filter_menu();

void products_filter_name_screen();

void products_filter_type_screen();

void products_filter_location_screen();

void products_filter_quantity_screen();

#define ID_INFO_MENU_DELETE 0
menu products_info_menu(product p);

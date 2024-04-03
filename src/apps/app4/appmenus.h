#pragma once

#include "../app.h"
#include "products.h"

enum Menus {
    app4, // app4_menu
    products_main, // products_main_menu
    products_view, // products_view_menu
    products_available, // products_available_menu
    products_filter, // products_filter_menu
    products_info, // products_info_menu
    reservations_main, // reservations_main_menu
    reservations_product, // reservations_product_menu
    reservations_info, // reservations_info_menu
};

extern product selected_product;
extern reservation selected_reservation;

#define ID_MAIN_MENU_PRODUCTS 0
#define ID_MAIN_MENU_RESERVATIONS 1
menu app4_menu();

#define ID_PRODUCTS_MAIN_MENU_VIEW 0
#define ID_PRODUCTS_MAIN_MENU_ADD 1
menu products_main_menu();

menu products_reservations_menu();

#define ID_PRODUCTS_VIEW_MENU_ALL 0
#define ID_PRODUCTS_VIEW_MENU_FILTER 1
menu products_view_menu();

void products_add_screen();

menu products_available_menu(product_array available);

#define ID_PRODUCTS_FILTER_MENU_NAME 0
#define ID_PRODUCTS_FILTER_MENU_TYPE 1
#define ID_PRODUCTS_FILTER_MENU_LOCATION 2
#define ID_PRODUCTS_FILTER_MENU_QUANTITY 3
#define ID_PRODUCTS_FILTER_MENU_APPLY 4
menu products_filter_menu();

void products_filter_name_screen();

void products_filter_type_screen();

void products_filter_location_screen();

void products_filter_quantity_screen();

#define ID_PRODUCTS_INFO_MENU_RESERVATIONS 0
#define ID_PRODUCTS_INFO_MENU_RESERVE 1
#define ID_PRODUCTS_INFO_MENU_DELETE 2
menu products_info_menu(product p);

menu reservations_main_menu();

void reservations_create_screen();

menu reservations_product_menu(product p);

#define ID_RESERVATIONS_INFO_MENU_CANCEL 0
menu reservations_info_menu(product p, reservation r);

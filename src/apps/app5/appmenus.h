#pragma once

#include "../app.h"

enum Menus {
    trains_main, // trains_main_menu
    trains, // trains_menu
    trains_view, // trains_view_menu
    trains_add, // trains_add_menu
    trains_all, // trains_available_menu
    trains_filter, // trains_filter_menu
    trains_filter_id, // trains_filter_id_menu
    wagons, // wagons_menu
    wagons_view, // wagons_view_menu
    wagons_add, // wagons_add_menu
    wagons_all, // wagons_available_menu
    wagons_filter, // wagons_filter_menu
    wagons_filter_id, // wagons_filter_id_menu
    wagons_filter_type, // wagons_filter_type_menu
};

#define ID_MAIN_MENU_TRAINS 0
#define ID_MAIN_MENU_WAGONS 1
menu trains_main_menu();

#define ID_TRAINS_MENU_VIEW 0
#define ID_TRAINS_MENU_ADD 1
menu trains_menu();

#define ID_TRAINS_VIEW_MENU_ALL 0
#define ID_TRAINS_VIEW_MENU_FILTER 1
menu trains_view_menu();

menu trains_add_menu();

menu trains_available_menu();

#define ID_TRAINS_FILTER_MENU_ID 0
#define ID_TRAINS_FILTER_MENU_APPLY 1
menu trains_filter_menu();

menu trains_filter_id_menu();

#define ID_WAGONS_MENU_VIEW 0
#define ID_WAGONS_MENU_ADD 1
menu wagons_menu();

#define ID_WAGONS_VIEW_MENU_ALL 0
#define ID_WAGONS_VIEW_MENU_FILTER 1
menu wagons_view_menu();

menu wagons_add_menu();

menu wagons_available_menu();

#define ID_WAGONS_FILTER_MENU_ID 0
#define ID_WAGONS_FILTER_MENU_TYPE 1
#define ID_WAGONS_FILTER_MENU_APPLY 2
menu wagons_filter_menu();

menu wagons_filter_id_menu();

menu wagons_filter_type_menu();

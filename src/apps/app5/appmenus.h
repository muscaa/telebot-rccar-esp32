#pragma once

#include "../app.h"

enum Menus {
    app5, // app5_menu
    locomotives_main, // locomotives_main_menu
    locomotives_view, // locomotives_view_menu
    locomotives_add, // locomotives_add_menu
    locomotives_all, // locomotives_available_menu
    locomotives_filter, // locomotives_filter_menu
    locomotives_filter_id, // locomotives_filter_id_menu
    wagons_main, // wagons_menu
    wagons_view, // wagons_view_menu
    wagons_add, // wagons_add_menu
    wagons_all, // wagons_available_menu
    wagons_filter, // wagons_filter_menu
    wagons_filter_id, // wagons_filter_id_menu
    wagons_filter_type, // wagons_filter_type_menu
};

#define ID_MAIN_MENU_LOCOMOTIVES 0
#define ID_MAIN_MENU_WAGONS 1
menu app5_menu();

#define ID_LOCOMOTIVES_MENU_VIEW 0
#define ID_LOCOMOTIVES_MENU_ADD 1
menu locomotives_main_menu();

#define ID_LOCOMOTIVES_VIEW_MENU_ALL 0
#define ID_LOCOMOTIVES_VIEW_MENU_FILTER 1
menu locomotives_view_menu();

menu locomotives_add_menu();

menu locomotives_available_menu();

#define ID_LOCOMOTIVES_FILTER_MENU_ID 0
#define ID_LOCOMOTIVES_FILTER_MENU_APPLY 1
menu locomotives_filter_menu();

menu locomotives_filter_id_menu();

#define ID_WAGONS_MENU_VIEW 0
#define ID_WAGONS_MENU_ADD 1
menu wagons_main_menu();

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

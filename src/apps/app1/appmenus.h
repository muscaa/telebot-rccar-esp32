#pragma once

#include "../app.h"
#include "rooms.h"

enum Menus {
    ID_MAIN_MENU,
    ID_ROOMS_MENU,
    ID_BOOKINGS_MENU,
    ID_VIEW_ROOMS_MENU
};

#define ID_MAIN_MENU_ROOMS 0
#define ID_MAIN_MENU_BOOKINGS 1
menu main_menu();

#define ID_ROOMS_MENU_VIEW 0
#define ID_ROOMS_MENU_ADD 1
menu rooms_menu();

menu bookings_menu();

menu view_rooms_menu();

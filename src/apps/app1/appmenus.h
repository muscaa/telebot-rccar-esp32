#pragma once

#include "../app.h"
#include "rooms.h"

enum Menus {
    app1, // app1_menu
    rooms, // rooms_menu
    rooms_bookings, // rooms_bookings_menu
    rooms_view, // rooms_view_menu
    rooms_add, // rooms_add_menu
    rooms_all, // rooms_available_menu
    rooms_filter, // rooms_filter_menu
    rooms_filter_name, // rooms_filter_name_menu
    rooms_filter_capacity, // rooms_filter_capacity_menu
    rooms_filter_availability, // rooms_filter_availability_menu
    rooms_room_info, // rooms_room_info_menu
    rooms_room_bookings, // rooms_room_bookings_menu
    rooms_booking_info, // rooms_booking_info_menu
};

#define ID_MAIN_MENU_ROOMS 0
#define ID_MAIN_MENU_BOOKINGS 1
menu app1_menu();

#define ID_ROOMS_MENU_VIEW 0
#define ID_ROOMS_MENU_ADD 1
menu rooms_menu();

menu rooms_bookings_menu();

#define ID_VIEW_MENU_ALL 0
#define ID_VIEW_MENU_FILTER 1
menu rooms_view_menu();

menu rooms_add_menu();

menu rooms_available_menu(int rooms_length, room function(get_room, int index));

#define ID_FILTER_MENU_NAME 0
#define ID_FILTER_MENU_CAPACITY 1
#define ID_FILTER_MENU_AVAILABILITY 2
#define ID_FILTER_MENU_APPLY 3
menu rooms_filter_menu();

menu rooms_filter_name_menu();

menu rooms_filter_capacity_menu();

menu rooms_filter_availability_menu();

#define ID_ROOM_INFO_MENU_BOOKINGS 0
#define ID_ROOM_INFO_MENU_BOOK 1
#define ID_ROOM_INFO_MENU_DELETE 2
menu rooms_room_info_menu(room r);

menu rooms_room_bookings_menu(room r);

#define ID_BOOKING_INFO_MENU_CANCEL 0
menu rooms_booking_info_menu(room r, booking b);

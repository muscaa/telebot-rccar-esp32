#pragma once

#include "../app.h"

enum Menus {
    app2, // app2_menu
    books, // books_menu
    books_borrowed, // books_borrowed_menu
    books_view, // books_view_menu
    books_add, // books_add_menu
    books_all, // books_available_menu
    books_filter, // books_filter_menu
    books_filter_title, // books_filter_title_menu
    books_filter_author, // books_filter_author_menu
    books_filter_type, // books_filter_type_menu
    books_filter_location, // books_filter_location_menu
    books_filter_availability // books_filter_availability_menu
};

#define ID_MAIN_MENU_BOOKS 0
#define ID_MAIN_MENU_BORROWED 1
menu app2_menu();

#define ID_BOOKS_MENU_VIEW 0
#define ID_BOOKS_MENU_ADD 1
menu books_menu();

menu books_borrowed_menu();

#define ID_VIEW_MENU_ALL 0
#define ID_VIEW_MENU_FILTER 1
menu books_view_menu();

menu books_add_menu();

menu books_available_menu();

#define ID_FILTER_MENU_TITLE 0
#define ID_FILTER_MENU_AUTHOR 1
#define ID_FILTER_MENU_TYPE 2
#define ID_FILTER_MENU_LOCATION 3
#define ID_FILTER_MENU_AVAILABILITY 4
#define ID_FILTER_MENU_APPLY 5
menu books_filter_menu();

menu books_filter_title_menu();

menu books_filter_author_menu();

menu books_filter_type_menu();

menu books_filter_location_menu();

menu books_filter_availability_menu();

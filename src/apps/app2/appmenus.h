#pragma once

#include "../app.h"

enum Menus {
    books_main, // main_menu
    books, // books_menu
    borrowed_books, // borrowed_books_menu
    view_books, // view_books_menu
    add_book, // add_book_menu
    all_books, // available_books_menu
    books_filter, // books_filter_menu
    books_filter_title, // books_filter_title_menu
    books_filter_author, // books_filter_author_menu
    books_filter_type, // books_filter_type_menu
    books_filter_location, // books_filter_location_menu
    books_filter_availability // books_filter_availability_menu
};

#define ID_MAIN_MENU_BOOKS 0
#define ID_MAIN_MENU_BORROWED 1
menu books_main_menu();

#define ID_BOOKS_MENU_VIEW 0
#define ID_BOOKS_MENU_ADD 1
menu books_menu();

menu borrowed_books_menu();

#define ID_VIEW_BOOKS_MENU_ALL_BOOKS 0
#define ID_VIEW_BOOKS_MENU_FILTER 1
menu view_books_menu();

menu add_book_menu();

menu available_books_menu();

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

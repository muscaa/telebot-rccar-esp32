/*
#2. Library books tracking system

The app allows adding/deleting a book with title, author, type and location,
displaying all books and borrowed books, searching for a book by title,
author and availability, borrowing the book and returning the borrowed book.
*/

#include "appmain.h"

#include "appmenus.h"

MENU(books_main,
    CASE_MENU(ID_MAIN_MENU_BOOKS, books)
    //CASE_MENU(ID_MAIN_MENU_BORROWED, borrowed_books)
    ,
    MENU(books,
        CASE_MENU(ID_BOOKS_MENU_VIEW, books_view)
        //CASE_MENU(ID_BOOKS_MENU_ADD, add_book)
        ,
        MENU(books_view,
            CASE(ID_VIEW_MENU_ALL,
                //MENU_SCREEN(all_books, available_books_menu());
            )
            CASE_MENU(ID_VIEW_MENU_FILTER, books_filter)
            ,
            //MENU(books_all,)
            MENU(books_filter,
                //CASE_MENU(ID_FILTER_MENU_TITLE, books_filter_title)
                //CASE_MENU(ID_FILTER_MENU_AUTHOR, books_filter_author)
                //CASE_MENU(ID_FILTER_MENU_TYPE, books_filter_type)
                //CASE_MENU(ID_FILTER_MENU_LOCATION, books_filter_location)
                //CASE_MENU(ID_FILTER_MENU_AVAILABILITY, books_filter_availability)
                CASE(ID_FILTER_MENU_APPLY,
                )
                ,
                //MENU(books_filter_title,)
                //MENU(books_filter_author,)
                //MENU(books_filter_type,)
                //MENU(books_filter_location,)
                //MENU(books_filter_availability,)
            )
        )
        //MENU(books_add,)
    )
    //MENU(books_borrowed,)
)

override
void app2_main(app a) {
    MENU_SCREEN(books_main, books_main_menu());
}

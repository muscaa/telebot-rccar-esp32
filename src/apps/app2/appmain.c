/*
#2. Library books tracking system

The system allows to store the data of the books in a library.
The user can add books by specifying title, author, types and location,
search and display books by title, author and availability, borrow
books for a number of days and return borrowed books.
*/

#include "appmain.h"

#include "appmenus.h"

MENU(books_main,
    CASE_MENU(ID_MAIN_MENU_BOOKS, books)
    CASE_MENU(ID_MAIN_MENU_BORROWED, borrowed_books)
    ,
    MENU(books,
        CASE_MENU(ID_BOOKS_MENU_VIEW, view_books)
        CASE_MENU(ID_BOOKS_MENU_ADD, add_book)
        ,
        MENU(view_books,
            CASE(ID_VIEW_BOOKS_MENU_ALL_BOOKS,
                MENU_SCREEN(all_books, available_books_menu());
            )
            CASE_MENU(ID_VIEW_BOOKS_MENU_FILTER, books_filter)
            ,
            MENU(all_books,
            )
            MENU(books_filter,
                CASE_MENU(ID_FILTER_MENU_TITLE, books_filter_title)
                CASE_MENU(ID_FILTER_MENU_AUTHOR, books_filter_author)
                CASE_MENU(ID_FILTER_MENU_TYPE, books_filter_type)
                CASE_MENU(ID_FILTER_MENU_LOCATION, books_filter_location)
                CASE_MENU(ID_FILTER_MENU_AVAILABILITY, books_filter_availability)
                ,
                MENU(books_filter_title,
                )
                MENU(books_filter_author,
                )
                MENU(books_filter_type,
                )
                MENU(books_filter_location,
                )
                MENU(books_filter_availability,
                )
            )
        )
        MENU(add_book,
        )
    )
    MENU(borrowed_books,
    )
)

override
void app2_main(app a) {
    MENU_SCREEN(books_main, books_main_menu());
}

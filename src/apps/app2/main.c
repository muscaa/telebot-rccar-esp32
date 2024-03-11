/*
#2. Library books tracking system

The system allows to store the data of the books in a library.
The user can add books by specifying title, author, type, location,
search and display books by title, author and availability, borrow
books for a number of days and return borrowed books.
*/

#include "main.h"

int app2_main() {
    if (dialog_yes_no("a title")) {
        println("pressed yes");
    } else {
        println("pressed no");
    }

    pause_console();
    return 0;
}
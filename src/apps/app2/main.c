/*
#2. Library books tracking system

The system allows to store the data of the books in a library.
App user can add books by specifying title, author, type, location,
search and display books by title, author and availability, borrow
books for a number of days (10 days) and return borrowed books.
Use the file manipulation mechanism to retrieve/save data from/to
the file. Also use data structures for information read from the file.
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
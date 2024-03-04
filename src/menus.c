#include "menus.h"
#include <stdio.h>

// PUBLIC
void main_menu() {
    clear_screen();

    option options[] = {
        new_option("Option 1", "This is the first option", COLOR_RED),
        new_option("Option 2", "This is the second option", COLOR_GREEN),
        new_option("Option 3", "This is the third option", COLOR_BLUE)
    };
    int option = vmenu("Main Menu", 3, options);

    println("You selected option %d", option);
}
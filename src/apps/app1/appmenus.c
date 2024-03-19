#include "appmenus.h"

override
menu main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION("Rooms", ID_MAIN_MENU_ROOMS));
    mcall(options, add, SELECTION("Bookings", ID_MAIN_MENU_BOOKINGS));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);

    /*new_action("Rooms", menu_rooms),
    new_action("Bookings", menu_bookings)*/

    return new(vmenu, options);
}

#include "appmenus.h"

override
menu main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION("Rooms", ID_MAIN_MENU_ROOMS));
    mcall(options, add, SELECTION("Bookings", ID_MAIN_MENU_BOOKINGS));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu rooms_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION("View rooms", ID_ROOMS_MENU_VIEW));
    mcall(options, add, SELECTION("Add room", ID_ROOMS_MENU_ADD));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu bookings_menu() {
    option_array options = new(option_array);
    for (int i = 0; i < get_rooms_length(); i++) {
        room r = get_room(i);
        if (r.bookings_length == 0) continue;

        mcall(options, add, SELECTION(format("%s (%d bookings)", r.name, r.bookings_length), i));
    }
    if (get_rooms_length() == 0) {
        mcall(options, add, option_separator()
                        ->name("No bookings available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu view_rooms_menu() {

}

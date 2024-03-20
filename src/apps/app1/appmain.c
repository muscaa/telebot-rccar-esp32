/*
#1. Meeting rooms reservation system

The user can view the available rooms and book a room.
The app allows adding/deleting a room with name and capacity,
displaying all rooms and bookings, searching for a room by name,
capacity and availability, booking the room and canceling the booking.
To book a room, the user must specify the date and time.
*/

#include "appmain.h"

#include "appmenus.h"
#include "rooms.h"

MENU(main,
    CASE_MENU(ID_MAIN_MENU_ROOMS, rooms)
    CASE_MENU(ID_MAIN_MENU_BOOKINGS, bookings)
    ,
    MENU(rooms,
        CASE_MENU(ID_ROOMS_MENU_VIEW, view_rooms)
        CASE_MENU(ID_ROOMS_MENU_ADD, add_room)
        ,
        MENU(view_rooms,
            CASE(ID_VIEW_ROOMS_MENU_ALL_ROOMS,
                MENU_SCREEN(all_rooms, available_rooms_menu(_get_rooms_length(), _get_room));
            )
            CASE_MENU(ID_VIEW_ROOMS_MENU_FILTER, filter)
            ,
            MENU(all_rooms,
                // open specific room menu
            )
            MENU(filter,
                CASE_MENU(ID_FILTER_MENU_FILTER_NAME, filter_name)
                CASE_MENU(ID_FILTER_MENU_FILTER_CAPACITY, filter_capacity)
                CASE_MENU(ID_FILTER_MENU_FILTER_AVAILABILITY, filter_availability)
                CASE(ID_FILTER_MENU_APPLY,
                    // apply filter
                )
                ,
                MENU(filter_name,
                    // filter name input
                )
                MENU(filter_capacity,
                    // filter capacity input
                )
                MENU(filter_availability,
                    // filter availability input
                )
            )
        )
        MENU(add_room,
            // room name input
            // room capacity input
        )
        MENU(room_info,
            // view bookings, book room, delete room
        )
    )
    MENU(bookings,
        // open specific booking menu
    )
)

override
void app1_main(app a) {
    _load_rooms();

    MENU_SCREEN(main, main_menu());
}

/*
#1. Meeting rooms booking system

The app allows adding/deleting a room with name and capacity,
displaying all rooms and bookings, searching for a room by name,
capacity and availability, booking the room and canceling the booking.
*/

#include "appmain.h"

#include "appmenus.h"
#include "rooms.h"

MENU(app1,
    CASE_MENU(ID_MAIN_MENU_ROOMS, rooms)
    CASE_MENU(ID_MAIN_MENU_BOOKINGS, rooms_bookings)
    ,
    MENU(rooms,
        CASE_MENU(ID_ROOMS_MENU_VIEW, rooms_view)
        //CASE_MENU(ID_ROOMS_MENU_ADD, rooms_add)
        ,
        MENU(rooms_view,
            CASE(ID_VIEW_MENU_ALL,
                MENU_SCREEN(rooms_all, rooms_available_menu(_get_rooms_length(), _get_room));
            )
            CASE_MENU(ID_VIEW_MENU_FILTER, rooms_filter)
            ,
            MENU(rooms_all,
                // open specific room menu
            )
            MENU(rooms_filter,
                //CASE_MENU(ID_FILTER_MENU_NAME, rooms_filter_name)
                //CASE_MENU(ID_FILTER_MENU_CAPACITY, rooms_filter_capacity)
                //CASE_MENU(ID_FILTER_MENU_AVAILABILITY, rooms_filter_availability)
                CASE(ID_FILTER_MENU_APPLY,
                )
                ,
                //MENU(rooms_filter_name,)
                //MENU(rooms_filter_capacity,)
                //MENU(rooms_filter_availability,)
            )
        )
        //MENU(rooms_add,)
        //MENU(rooms_room_info,)
    )
    MENU(rooms_bookings,
    )
)

override
void app1_main(app a) {
    _load_rooms();

    MENU_SCREEN(app1, app1_menu());
}

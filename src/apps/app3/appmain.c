/*
#3. Bicycle reservation system

The app allows adding/deleting a bike with type and location,
displaying all bikes and reservations, searching for a bike by type
and availability, reserving the bike and canceling the reservation.
*/

#include "appmain.h"

#include "appmenus.h"

MENU(bikes_main,
    CASE_MENU(ID_MAIN_MENU_BIKES, bikes)
    //CASE_MENU(ID_MAIN_MENU_RESERVATIONS, bikes_reservations)
    ,
    MENU(bikes,
        CASE_MENU(ID_BIKES_MENU_VIEW, bikes_view)
        //CASE_MENU(ID_BIKES_MENU_ADD, bikes_add)
        ,
        MENU(bikes_view,
            CASE(ID_VIEW_MENU_ALL,
                //MENU_SCREEN(bikes_all, bikes_available_menu());
            )
            CASE_MENU(ID_VIEW_MENU_FILTER, bikes_filter)
            ,
            MENU(bikes_filter,
                //CASE_MENU(ID_FILTER_MENU_TYPE, bikes_filter_type)
                //CASE_MENU(ID_FILTER_MENU_LOCATION, bikes_filter_location)
                //CASE_MENU(ID_FILTER_MENU_AVAILABILITY, bikes_filter_availability)
                CASE(ID_FILTER_MENU_APPLY,
                )
                ,
                //MENU(bikes_filter_type,)
                //MENU(bikes_filter_location,)
                //MENU(bikes_filter_availability,)
            )
            //MENU(bikes_all,)
        )
        //MENU(bikes_add,)
    )
    //MENU(bikes_reservations,)
)

override
void app3_main(app a) {
    MENU_SCREEN(bikes_main, bikes_main_menu());
}

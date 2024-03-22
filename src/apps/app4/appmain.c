/*
#4. Pharmacy products reservation system

The app allows adding/deleting a product with name, type and location,
displaying all products and reservations, searching for a product by name
and availability, reserving the product and canceling the reservation.
*/

#include "appmain.h"

#include "appmenus.h"

MENU(app4,
    CASE_MENU(ID_MAIN_MENU_PRODUCTS, products)
    //CASE_MENU(ID_MAIN_MENU_RESERVATIONS, products_reservations)
    ,
    MENU(products,
        CASE_MENU(ID_PRODUCTS_MENU_VIEW, products_view)
        //CASE_MENU(ID_PRODUCTS_MENU_ADD, products_add)
        ,
        MENU(products_view,
            CASE(ID_VIEW_MENU_ALL,
                //MENU_SCREEN(products_all, products_available_menu());
            )
            CASE_MENU(ID_VIEW_MENU_FILTER, products_filter)
            ,
            MENU(products_filter,
                //CASE_MENU(ID_FILTER_MENU_NAME, products_filter_name)
                //CASE_MENU(ID_FILTER_MENU_LOCATION, products_filter_location)
                //CASE_MENU(ID_FILTER_MENU_AVAILABILITY, products_filter_availability)
                CASE(ID_FILTER_MENU_APPLY,
                )
                ,
                //MENU(products_filter_name,)
                //MENU(products_filter_location,)
                //MENU(products_filter_availability,)
            )
            //MENU(products_all,)
        )
        //MENU(products_add,)
    )
    //MENU(products_reservations,)
)

override
void app4_main(app a) {
    MENU_SCREEN(app4, app4_menu());
}

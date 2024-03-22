/*
#5. Train tracking system

The app allows adding/deleting a locomotive with an id, adding/deleting
a wagon with id and type, displaying all locomotives and wagons, searching
for a locomotive by id, searching for a wagon by id and type, creating trains by
coupling/decoupling wagons from/to a locomotive.
*/

#include "appmain.h"

#include "appmenus.h"
#include "trains.h"

MENU(trains_main,
    CASE_MENU(ID_MAIN_MENU_TRAINS, trains)
    CASE_MENU(ID_MAIN_MENU_WAGONS, wagons)
    ,
    MENU(trains,
        CASE_MENU(ID_TRAINS_MENU_VIEW, trains_view)
        //CASE_MENU(ID_TRAINS_MENU_ADD, trains_add)
        CASE(ID_TRAINS_MENU_ADD,
            
        )
        ,
        MENU(trains_view,
            CASE(ID_TRAINS_VIEW_MENU_ALL,
                //MENU_SCREEN(trains_all, trains_available_menu());
            )
            CASE_MENU(ID_TRAINS_VIEW_MENU_FILTER, trains_filter)
            ,
            //MENU(trains_all,)
            MENU(trains_filter,
                //CASE_MENU(ID_TRAINS_FILTER_MENU_ID, trains_filter_id)
                CASE(ID_TRAINS_FILTER_MENU_APPLY,
                )
                ,
                //MENU(trains_filter_id,)
            )
        )
        //MENU(trains_add,)
    )
    MENU(wagons,
        CASE_MENU(ID_WAGONS_MENU_VIEW, wagons_view)
        //CASE_MENU(ID_WAGONS_MENU_ADD, wagons_add)
        ,
        MENU(wagons_view,
            CASE(ID_WAGONS_VIEW_MENU_ALL,
                //MENU_SCREEN(wagons_all, wagons_available_menu());
            )
            CASE_MENU(ID_WAGONS_VIEW_MENU_FILTER, wagons_filter)
            ,
            //MENU(wagons_all,)
            MENU(wagons_filter,
                //CASE_MENU(ID_WAGONS_FILTER_MENU_ID, wagons_filter_id)
                //CASE_MENU(ID_WAGONS_FILTER_MENU_TYPE, wagons_filter_type)
                CASE(ID_WAGONS_FILTER_MENU_APPLY,
                )
                ,
                //MENU(wagons_filter_id,)
                //MENU(wagons_filter_type,)
            )
        )
        //MENU(wagons_add,)
    )
)

override
void app5_main(app a) {
    init_trains();

    MENU_SCREEN(trains_main, trains_main_menu());
}

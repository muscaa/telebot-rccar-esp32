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

MENU(app5,
    CASE_MENU(ID_MAIN_MENU_LOCOMOTIVES, locomotives_main)
    CASE_MENU(ID_MAIN_MENU_WAGONS, wagons_main)
    ,
    MENU(locomotives_main,
        CASE_MENU(ID_LOCOMOTIVES_MENU_VIEW, locomotives_view)
        //CASE_MENU(ID_LOCOMOTIVES_MENU_ADD, locomotives_add)
        CASE(ID_LOCOMOTIVES_MENU_ADD,
            
        )
        ,
        MENU(locomotives_view,
            CASE(ID_LOCOMOTIVES_VIEW_MENU_ALL,
                //MENU_SCREEN(locomotives_all, locomotives_available_menu());
            )
            CASE_MENU(ID_LOCOMOTIVES_VIEW_MENU_FILTER, locomotives_filter)
            ,
            //MENU(locomotives_all,)
            MENU(locomotives_filter,
                //CASE_MENU(ID_LOCOMOTIVES_FILTER_MENU_ID, locomotives_filter_id)
                CASE(ID_LOCOMOTIVES_FILTER_MENU_APPLY,
                )
                ,
                //MENU(locomotives_filter_id,)
            )
        )
        //MENU(locomotives_add,)
    )
    MENU(wagons_main,
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

    MENU_SCREEN(app5, app5_menu());
}

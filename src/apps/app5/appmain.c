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

MENU(wagons_available,
    default: {
        wagon w = mcall(wagons, get, opt->id);
        MENU_SCREEN(wagons_info, wagons_info_menu(w));
    }
    ,
    MENU(wagons_info,
        // delete, couple etc
    )
)

MENU(trains_available,
    default: {
        train t = mcall(trains, get, opt->id);
        MENU_SCREEN(trains_info, trains_info_menu(t));
    }
    ,
    MENU(trains_info,
    )
)

MENU(app5,
    CASE_MENU(ID_MAIN_MENU_TRAINS, trains_main)
    CASE_MENU(ID_MAIN_MENU_WAGONS, wagons_main)
    ,
    MENU(trains_main,
        CASE_MENU(ID_TRAINS_MENU_VIEW, trains_view)
        CASE(ID_TRAINS_MENU_ADD,
            trains_add_screen();
        )
        ,
        MENU(trains_view,
            CASE(ID_TRAINS_VIEW_MENU_ALL,
                MENU_SCREEN(trains_available, trains_available_menu(trains));
            )
            CASE_MENU(ID_TRAINS_VIEW_MENU_FILTER, trains_filter)
            ,
            MENU(trains_filter,
                CASE(ID_TRAINS_FILTER_MENU_ID,
                    trains_filter_id_screen();
                )
                CASE(ID_TRAINS_FILTER_MENU_APPLY,
                    trains_apply_filter();
                    MENU_SCREEN(trains_available, trains_available_menu(trains_filtered));
                )
            )
        )
    )
    MENU(wagons_main,
        CASE_MENU(ID_WAGONS_MENU_VIEW, wagons_view)
        CASE(ID_WAGONS_MENU_ADD,
            wagons_add_screen();
        )
        ,
        MENU(wagons_view,
            CASE(ID_WAGONS_VIEW_MENU_ALL,
                MENU_SCREEN(wagons_available, wagons_available_menu(wagons));
            )
            CASE_MENU(ID_WAGONS_VIEW_MENU_FILTER, wagons_filter)
            ,
            MENU(wagons_filter,
                CASE(ID_WAGONS_FILTER_MENU_ID,
                    wagons_filter_id_screen();
                )
                CASE(ID_WAGONS_FILTER_MENU_TYPE,
                    wagons_filter_type_screen();
                )
                CASE(ID_WAGONS_FILTER_MENU_APPLY,
                    wagons_apply_filter();
                    MENU_SCREEN(wagons_available, wagons_available_menu(wagons_filtered));
                )
            )
        )
    )
)

override
void app5_main(app a) {
    init_trains();

    MENU_SCREEN(app5, app5_menu());
}

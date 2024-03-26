/*
#5. Train tracking system

The app allows adding/deleting a train with an id, adding/deleting
a wagon with id and type, displaying all trains and wagons, searching
for a train by id, searching for a wagon by id and type and
coupling/decoupling wagons from/to a train.
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
        CASE(ID_WAGONS_INFO_MENU_DELETE,
            int index = mcall(m->options, get, 0)->id;
            wagon w = mcall(wagons, get, index);

            remove_wagon(w->id);

            screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
            menu prev_menu = mcall(prev_screen->components, get, 2)->data;

            if (prev_menu->options->length == 4) {
                mcall(prev_menu->options, set, 0, option_separator()
                                ->name("No wagons available.")
                                ->build());
            } else {
                int i;
                for (i = 0; i < prev_menu->options->length - 3; i++) {
                    option opt = mcall(prev_menu->options, get, i);
                    if (opt->id == index) {
                        mcall(prev_menu->options, remove, i);
                        break;
                    }
                }
                for (; i < prev_menu->options->length - 3; i++) {
                    option o = mcall(prev_menu->options, get, i);
                    o->id--;
                }
            }

            mcall0(render_stack, pop);
        )
        CASE(ID_WAGONS_INFO_MENU_COUPLE,
            int index = mcall(m->options, get, 0)->id;
            wagon w = mcall(wagons, get, index);

            MENU_SCREEN(wagons_couple, wagons_couple_menu(w));
        )
        ,
        MENU(wagons_couple,
            default: {
                int index = mcall(m->options, get, 0)->id;
                wagon w = mcall(wagons, get, index);
                train t = mcall(trains, get, opt->id);

                couple(t, w);

                screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
                menu prev_menu = mcall(prev_screen->components, get, 2)->data;

                int uses = 0;
                for (int i = 0; i < trains->length; i++) {
                    train t = mcall(trains, get, i);
                    
                    coupled_wagon cw = t->next_wagon;
                    while (cw != NULL) {
                        int cw_index = find_wagon(cw->wagon->id);
                        if (cw_index == index) {
                            uses++;
                        }
                        cw = cw->next_wagon;
                    }
                }
                mcall(prev_menu->options, set, 3, uses == 0 ? 
                                SELECTION(ID_WAGONS_INFO_MENU_DELETE, "Delete") :
                                option_separator()
                                        ->name(format("Delete (%d uses)", uses))
                                        ->build()
                );

                mcall0(render_stack, pop);
            }
        )
    )
)

MENU(trains_available,
    default: {
        train t = mcall(trains, get, opt->id);
        MENU_SCREEN(trains_info, trains_info_menu(t));
    }
    ,
    MENU(trains_info,
        CASE(ID_TRAINS_INFO_MENU_DELETE,
            int index = mcall(m->options, get, 0)->id;
            train t = mcall(trains, get, index);

            remove_train(t->id);

            screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
            menu prev_menu = mcall(prev_screen->components, get, 2)->data;

            if (prev_menu->options->length == 4) {
                mcall(prev_menu->options, set, 0, option_separator()
                                ->name("No trains available.")
                                ->build());
            } else {
                int i;
                for (i = 0; i < prev_menu->options->length - 3; i++) {
                    option opt = mcall(prev_menu->options, get, i);
                    if (opt->id == index) {
                        mcall(prev_menu->options, remove, i);
                        break;
                    }
                }
                for (; i < prev_menu->options->length - 3; i++) {
                    option o = mcall(prev_menu->options, get, i);
                    o->id--;
                }
            }

            mcall0(render_stack, pop);
        )
        CASE(ID_TRAINS_INFO_MENU_WAGONS,
            int index = mcall(m->options, get, 0)->id;
            train t = mcall(trains, get, index);

            MENU_SCREEN(trains_wagons, trains_wagons_menu(t));
        )
        ,
        MENU(trains_wagons,
            default: {
                int index = mcall(m->options, get, 0)->id;
                train t = mcall(trains, get, index);

                coupled_wagon cw = t->next_wagon;
                for (int i = 0; i < opt->id; i++) {
                    cw = cw->next_wagon;
                }

                MENU_SCREEN(trains_wagons_info, trains_wagons_info_menu(cw));
            }
            ,
            MENU(trains_wagons_info,
                CASE(ID_TRAINS_WAGONS_INFO_MENU_DECOUPLE,
                    int train_index = mcall(m->options, get, 0)->id;
                    train t = mcall(trains, get, train_index);

                    int wagon_index = mcall(m->options, get, 1)->id;
                    coupled_wagon cw = t->next_wagon;
                    for (int i = 0; i < wagon_index; i++) {
                        cw = cw->next_wagon;
                    }

                    screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
                    menu prev_menu = mcall(prev_screen->components, get, 2)->data;

                    if (prev_menu->options->length == 6) {
                        mcall(prev_menu->options, set, 2, option_separator()
                                        ->name("No coupled wagons.")
                                        ->build());
                    } else {
                        int i;
                        for (i = 2; i < prev_menu->options->length - 3; i++) {
                            option opt = mcall(prev_menu->options, get, i);
                            if (opt->id == wagon_index) {
                                mcall(prev_menu->options, remove, i);
                                break;
                            }
                        }
                        for (; i < prev_menu->options->length - 3; i++) {
                            option o = mcall(prev_menu->options, get, i);
                            o->id--;
                        }
                    }

                    decouple(cw);

                    mcall0(render_stack, pop);
                )
            )
        )
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

/*
#4. Pharmacy products reservation system

The app allows adding/deleting a product with name, type and location,
displaying all products and reservations, searching for a product by name
and availability, reserving the product and canceling the reservation.
*/

#include "appmain.h"

#include "appmenus.h"
#include "products.h"

private product selected = NULL;

MENU(products_available,
    default: {
        selected = mcall(products, get, opt->id);
        MENU_SCREEN(products_info, products_info_menu(selected));
    }
    ,
    MENU(products_info,
        CASE(ID_INFO_MENU_DELETE,
            int index = find_product(selected->name);

            remove_product(selected->name);

            screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
            menu prev_menu = mcall(prev_screen->components, get, 2)->data;

            if (prev_menu->options->length == 4) { // product, separator, back, main menu
                mcall(prev_menu->options, set, 0, option_separator()
                                ->name("No wagons available.")
                                ->build());
            } else {
                int i = 0;
                for (; i < prev_menu->options->length - 3; i++) {
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
    )
)

MENU(app4,
    CASE_MENU(ID_MAIN_MENU_PRODUCTS, products_main)
    //CASE_MENU(ID_MAIN_MENU_RESERVATIONS, products_reservations)
    ,
    MENU(products_main,
        CASE_MENU(ID_PRODUCTS_MENU_VIEW, products_view)
        CASE(ID_PRODUCTS_MENU_ADD,
            products_add_screen();
        )
        ,
        MENU(products_view,
            CASE(ID_VIEW_MENU_ALL,
                MENU_SCREEN(products_available, products_available_menu(products));
            )
            CASE_MENU(ID_VIEW_MENU_FILTER, products_filter)
            ,
            MENU(products_filter,
                CASE(ID_FILTER_MENU_NAME,
                    products_filter_name_screen();
                )
                CASE(ID_FILTER_MENU_TYPE,
                    products_filter_type_screen();
                )
                CASE(ID_FILTER_MENU_LOCATION,
                    products_filter_location_screen();
                )
                CASE(ID_FILTER_MENU_QUANTITY,
                    products_filter_quantity_screen();
                )
                CASE(ID_FILTER_MENU_APPLY,
                    products_apply_filter();
                    MENU_SCREEN(products_available, products_available_menu(products_filtered));
                )
            )
        )
    )
    //MENU(products_reservations,)
)

override
void app4_main(app a) {
    init_products();

    MENU_SCREEN(app4, app4_menu());
}

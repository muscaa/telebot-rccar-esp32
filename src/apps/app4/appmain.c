/*
#4. Pharmacy products reservation system

The app allows adding/deleting a product with name, type and location,
displaying all products and reservations, searching for a product by name
and availability, reserving the product and canceling the reservation.
*/

#include "appmain.h"

#include "appmenus.h"
#include "products.h"

MENU(reservations_product,
    default: {
        selected_reservation = mcall(selected_product->reservations, get, opt->id);
        MENU_SCREEN(reservations_info, reservations_info_menu(selected_product, selected_reservation));
    }
    ,
    MENU(reservations_info,
        CASE(ID_RESERVATIONS_INFO_MENU_CANCEL,
            int index = 0;
            for (; index < selected_product->reservations->length; index++) {
                reservation r = mcall(selected_product->reservations, get, index);

                if (mcall(selected_reservation->uid, equals, r->uid)) break;
            }
            cancel_reservation(selected_product, selected_reservation->uid);
            remove_option_and_decrement_after(prev_menu(), index, "No reservations available.");

            mcall0(render_stack, pop);
        )
    )
)

MENU(products_info,
    CASE(ID_PRODUCTS_INFO_MENU_RESERVATIONS,
        MENU_SCREEN(reservations_product, reservations_product_menu(selected_product));
    )
    CASE(ID_PRODUCTS_INFO_MENU_RESERVE,
        reservations_create_screen();
    )
    CASE(ID_PRODUCTS_INFO_MENU_DELETE,
        int index = find_product(selected_product->name);
        remove_product(selected_product->name);
        remove_option_and_decrement_after(prev_menu(), index, "No products available.");

        mcall0(render_stack, pop);
    )
)

MENU(app4,
    CASE_MENU(ID_MAIN_MENU_PRODUCTS, products_main)
    CASE_MENU(ID_MAIN_MENU_RESERVATIONS, reservations_main)
    ,
    MENU(products_main,
        CASE_MENU(ID_PRODUCTS_MAIN_MENU_VIEW, products_view)
        CASE(ID_PRODUCTS_MAIN_MENU_ADD,
            products_add_screen();
        )
        ,
        MENU(products_view,
            CASE(ID_PRODUCTS_VIEW_MENU_ALL,
                MENU_SCREEN(products_available, products_available_menu(products));
            )
            CASE_MENU(ID_PRODUCTS_VIEW_MENU_FILTER, products_filter)
            ,
            MENU(products_available,
                default: {
                    selected_product = mcall(products, get, opt->id);
                    MENU_SCREEN(products_info, products_info_menu(selected_product));
                }
            )
            MENU(products_filter,
                CASE(ID_PRODUCTS_FILTER_MENU_NAME,
                    products_filter_name_screen();
                )
                CASE(ID_PRODUCTS_FILTER_MENU_TYPE,
                    products_filter_type_screen();
                )
                CASE(ID_PRODUCTS_FILTER_MENU_LOCATION,
                    products_filter_location_screen();
                )
                CASE(ID_PRODUCTS_FILTER_MENU_QUANTITY,
                    products_filter_quantity_screen();
                )
                CASE(ID_PRODUCTS_FILTER_MENU_APPLY,
                    products_apply_filter();
                    MENU_SCREEN(products_available, products_available_menu(products_filtered));
                )
            )
        )
    )
    MENU(reservations_main,
        default: {
            selected_product = mcall(products, get, opt->id);
            MENU_SCREEN(reservations_product, reservations_product_menu(selected_product));
        }
    )
)

override
void app4_main(app a) {
    init_products();

    MENU_SCREEN(app4, app4_menu());
}

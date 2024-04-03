#include "appmenus.h"

#include "products.h"

#define INPUT_NAME \
    new(input_builder) \
    ->max_length(16) \
    ->accepts("az|AZ|09| ")

#define INPUT_TYPE \
    new(input_builder) \
    ->max_length(16) \
    ->accepts("az|AZ|09| ")

#define INPUT_LOCATION \
    new(input_builder) \
    ->max_length(32) \
    ->accepts("az|AZ|09| |-")

#define INPUT_QUANTITY \
    new(input_builder) \
    ->max_length(8) \
    ->accepts("09")

override
menu app4_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_PRODUCTS, "Products"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_RESERVATIONS, "Reservations"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_PRODUCTS_MENU_VIEW, "View products"));
    mcall(options, add, SELECTION(ID_PRODUCTS_MENU_ADD, "Add product"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_reservations_menu() {
    return NULL;
}

override
menu products_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_VIEW_MENU_ALL, "All products"));
    mcall(options, add, SELECTION(ID_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

private void products_add_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 0) {
        insert_component(s, ID_BACK, -1, label, new(label, "Product type: "));
        insert_component(s, ID_BACK, 1, input, INPUT_TYPE
                        ->build());
    } else if (c->id == 1) {
        insert_component(s, ID_BACK, -1, label, new(label, "Product location: "));
        insert_component(s, ID_BACK, 2, input, INPUT_LOCATION
                        ->build());
    } else if (c->id == 2) {
        insert_component(s, ID_BACK, -1, label, new(label, "Product quantity: "));
        insert_component(s, ID_BACK, 3, input, INPUT_QUANTITY
                        ->build());
    } else if (c->id == 3) {
        input name = mcall(s, get, 0)->data;
        input type = mcall(s, get, 1)->data;
        input location = mcall(s, get, 2)->data;
        input quantity = mcall(s, get, 3)->data;

        add_product(name->result, type->result, location->result, atoi(quantity->result));

        mcall0(render_stack, pop);
    }
}

override
void products_add_screen() {
    screen s = mcall(render_stack, push, products_add_action);
    add_component(s, -1, label, new(label, "Product name: "));
    add_component(s, 0, input, INPUT_NAME
                    ->exists(product_exists)
                    ->build());
    CANCEL_WITH_ESC(s);
}

override
menu products_available_menu(product_array available) {
    option_array options = new(option_array);
    for (int i = 0; i < available->length; i++) {
        product p = mcall(available, get, i);
        int index = find_product(p->name);

        mcall(options, add, SELECTION(index, p->name));
    }
    if (available->length == 0) {
        mcall(options, add, option_separator()
                        ->name("No products available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu products_filter_menu() {
    products_reset_filter();

    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_FILTER_MENU_NAME, "Name filter"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_TYPE, "Type filter"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_LOCATION, "Location filter"));
    mcall(options, add, SELECTION(ID_FILTER_MENU_QUANTITY, "Quantity filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

private void products_filter_name_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 0) {
        input in = mcall(s, get, 0)->data;
        products_name_filter = strlen(in->result) == 0 ? NULL : in->result;

        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, ID_FILTER_MENU_NAME,
                SELECTION(ID_FILTER_MENU_NAME,
                        concat("Name filter", products_name_filter != NULL ?
                            format(" (%s)", products_name_filter) : ""
                        )
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void products_filter_name_screen() {
    screen s = mcall(render_stack, push, products_filter_name_action);
    add_component(s, -1, label, new(label, "Name filter: "));
    add_component(s, 0, input, INPUT_NAME
                    ->value(products_name_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

private void products_filter_type_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 0) {
        input in = mcall(s, get, 0)->data;
        products_type_filter = strlen(in->result) == 0 ? NULL : in->result;

        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, ID_FILTER_MENU_TYPE,
                SELECTION(ID_FILTER_MENU_TYPE,
                        concat("Type filter", products_type_filter != NULL ?
                            format(" (%s)", products_type_filter) : ""
                        )
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void products_filter_type_screen() {
    screen s = mcall(render_stack, push, products_filter_type_action);
    add_component(s, -1, label, new(label, "Type filter: "));
    add_component(s, 0, input, INPUT_TYPE
                    ->value(products_type_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

private void products_filter_location_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 0) {
        input in = mcall(s, get, 0)->data;
        products_location_filter = strlen(in->result) == 0 ? NULL : in->result;

        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, ID_FILTER_MENU_LOCATION,
                SELECTION(ID_FILTER_MENU_LOCATION,
                        concat("Location filter", products_location_filter != NULL ?
                            format(" (%s)", products_location_filter) : ""
                        )
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void products_filter_location_screen() {
    screen s = mcall(render_stack, push, products_filter_location_action);
    add_component(s, -1, label, new(label, "Location filter: "));
    add_component(s, 0, input, INPUT_LOCATION
                    ->value(products_location_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

private void products_filter_quantity_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 0) {
        input in = mcall(s, get, 0)->data;
        products_quantity_filter = strlen(in->result) == 0 ? NULL : in->result;

        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, ID_FILTER_MENU_QUANTITY,
                SELECTION(ID_FILTER_MENU_QUANTITY,
                        concat("Quantity filter", products_quantity_filter != NULL ?
                            format(" (%s)", products_quantity_filter) : ""
                        )
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void products_filter_quantity_screen() {
    screen s = mcall(render_stack, push, products_filter_quantity_action);
    add_component(s, -1, label, new(label, "Quantity filter: "));
    add_component(s, 0, input, INPUT_QUANTITY
                    ->value(products_quantity_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

override
menu products_info_menu(product p) {
    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->name(format("Product name: %s", p->name))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Product type: %s", p->type))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Product location: %s", p->location))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Product quantity: %d", p->quantity))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Product available quantity: %d", mcall0(p, available_quantity)))
                    ->build());
    // how much is reserved
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_INFO_MENU_DELETE, "Delete"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

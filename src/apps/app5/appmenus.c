#include "appmenus.h"

#define INPUT_ID \
    new(input_builder) \
    ->max_length(16) \
    ->accepts("az|09|_")

#define INPUT_TYPE \
    new(input_builder) \
    ->max_length(16) \
    ->accepts("az|AZ|09| ")

override
menu app5_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_MAIN_MENU_TRAINS, "Trains"));
    mcall(options, add, SELECTION(ID_MAIN_MENU_WAGONS, "Wagons"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_TRAINS_MENU_VIEW, "View trains"));
    mcall(options, add, SELECTION(ID_TRAINS_MENU_ADD, "Add train"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_TRAINS_VIEW_MENU_ALL, "View all"));
    mcall(options, add, SELECTION(ID_TRAINS_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

private void trains_add_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 2) {
        input id = mcall(s, get, 2)->data;

        add_train(id->result);

        mcall0(render_stack, pop);
    }
}

override
void trains_add_screen() {
    screen s = mcall(render_stack, push, trains_add_action);
    add_component(s, -1, label, new(label, "Train ID: "));
    add_component(s, 2, input, INPUT_ID
                    ->exists(train_exists)
                    ->build());
    CANCEL_WITH_ESC(s);
}

override
menu trains_available_menu(train_array available) {
    option_array options = new(option_array);
    for (int i = 0; i < available->length; i++) {
        train t = mcall(available, get, i);
        int index = find_train(t->id);

        mcall(options, add, SELECTION(index, t->id));
    }
    if (available->length == 0) {
        mcall(options, add, option_separator()
                        ->name("No trains available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_filter_menu() {
    trains_reset_filter();

    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_TRAINS_FILTER_MENU_ID, "Filter ID"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_TRAINS_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

private void trains_filter_id_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 2) {
        input id = mcall(s, get, 2)->data;
        trains_id_filter = strlen(id->result) == 0 ? NULL : id->result;

        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, 0,
                SELECTION(ID_WAGONS_FILTER_MENU_ID,
                trains_id_filter == NULL ?
                        "Filter ID" :
                        format("Filter ID (%s)", trains_id_filter)
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void trains_filter_id_screen() {
    screen s = mcall(render_stack, push, trains_filter_id_action);
    add_component(s, -1, label, new(label, "ID filter: "));
    add_component(s, 2, input, INPUT_ID
                    ->value(trains_id_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

override
menu trains_info_menu(train t) {
    int index = find_train(t->id);

    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->id(index)
                    ->name(format("Train ID: %s", t->id))
                    ->build());
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_TRAINS_INFO_MENU_DELETE, "Delete"));
    mcall(options, add, SELECTION(ID_TRAINS_INFO_MENU_WAGONS, "Coupled wagons"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_wagons_menu(train t) {
    int index = find_train(t->id);

    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->id(index)
                    ->name(t->id)
                    ->build());
    mcall(options, add, SEPARATOR);

    coupled_wagon head = t->next_wagon;
    if (head == NULL) {
        mcall(options, add, option_separator()
                        ->name("No coupled wagons.")
                        ->build());
    }
    for (int i = 0; head != NULL; i++, head = head->next_wagon) {
        mcall(options, add, SELECTION(i, head->wagon->id));
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu trains_wagons_info_menu(coupled_wagon cw) {
    int index = 0;
    coupled_wagon head = cw;
    while (head->prev_type != TYPE_TRAIN) {
        head = head->prev_wagon.wagon;
        index++;
    }
    int train_index = find_train(head->prev_wagon.train->id);

    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->id(train_index)
                    ->name(format("Wagon ID: %s", cw->wagon->id))
                    ->build());
    mcall(options, add, option_separator()
                    ->id(index)
                    ->name(format("Wagon type: %s", cw->wagon->type))
                    ->build());
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_TRAINS_WAGONS_INFO_MENU_DECOUPLE, "Decouple"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_main_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_WAGONS_MENU_VIEW, "View wagons"));
    mcall(options, add, SELECTION(ID_WAGONS_MENU_ADD, "Add wagon"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_view_menu() {
    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_WAGONS_VIEW_MENU_ALL, "View all"));
    mcall(options, add, SELECTION(ID_WAGONS_VIEW_MENU_FILTER, "Filter"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

private void wagons_add_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 2) {
        insert_component(s, ID_BACK, -1, label, new(label, "Wagon type: "));
        insert_component(s, ID_BACK, 3, input, INPUT_TYPE
                        ->build());
    } else if (c->id == 3) {
        input id = mcall(s, get, 2)->data;
        input type = mcall(s, get, 3)->data;

        add_wagon(id->result, type->result);

        mcall0(render_stack, pop);
    }
}

override
void wagons_add_screen() {
    screen s = mcall(render_stack, push, wagons_add_action);
    add_component(s, -1, label, new(label, "Wagon ID: "));
    add_component(s, 2, input, INPUT_ID
                    ->exists(wagon_exists)
                    ->build());
    CANCEL_WITH_ESC(s);
}

override
menu wagons_available_menu(wagon_array available) {
    option_array options = new(option_array);
    for (int i = 0; i < available->length; i++) {
        wagon w = mcall(available, get, i);
        int index = find_wagon(w->id);

        mcall(options, add, SELECTION(index, w->id));
    }
    if (available->length == 0) {
        mcall(options, add, option_separator()
                        ->name("No wagons available.")
                        ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_filter_menu() {
    wagons_reset_filter();

    option_array options = new(option_array);
    mcall(options, add, SELECTION(ID_WAGONS_FILTER_MENU_ID, "Filter ID"));
    mcall(options, add, SELECTION(ID_WAGONS_FILTER_MENU_TYPE, "Filter type"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, SELECTION(ID_WAGONS_FILTER_MENU_APPLY, "Apply"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

private void wagons_filter_id_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 2) {
        input id = mcall(s, get, 2)->data;
        wagons_id_filter = strlen(id->result) == 0 ? NULL : id->result;

        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, 0,
                SELECTION(ID_WAGONS_FILTER_MENU_ID,
                wagons_id_filter == NULL ?
                        "Filter ID" :
                        format("Filter ID (%s)", wagons_id_filter)
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void wagons_filter_id_screen() {
    screen s = mcall(render_stack, push, wagons_filter_id_action);
    add_component(s, -1, label, new(label, "ID filter: "));
    add_component(s, 2, input, INPUT_ID
                    ->value(wagons_id_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

private void wagons_filter_type_action(component c) {
    screen s = c->parent;

    if (c->id == ID_BACK) {
        mcall0(render_stack, pop);
    } else if (c->id == 2) {
        input type = mcall(s, get, 2)->data;
        wagons_type_filter = strlen(type->result) == 0 ? NULL : type->result;
        
        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2);
        menu prev_menu = mcall(prev_screen->components, get, 2)->data;

        mcall(prev_menu->options, set, 1,
                SELECTION(ID_WAGONS_FILTER_MENU_ID,
                wagons_type_filter == NULL ?
                        "Filter type" :
                        format("Filter type (%s)", wagons_type_filter)
                )
        );

        mcall0(render_stack, pop);
    }
}

override
void wagons_filter_type_screen() {
    screen s = mcall(render_stack, push, wagons_filter_type_action);
    add_component(s, -1, label, new(label, "Type filter: "));
    add_component(s, 2, input, INPUT_TYPE
                    ->value(wagons_type_filter)
                    ->allow_empty()
                    ->build());
    CANCEL_WITH_ESC(s);
}

override
menu wagons_info_menu(wagon w) {
    int index = find_wagon(w->id);

    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->id(index)
                    ->name(format("Wagon ID: %s", w->id))
                    ->build());
    mcall(options, add, option_separator()
                    ->name(format("Wagon type: %s", w->type))
                    ->build());
    mcall(options, add, SEPARATOR);

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
    mcall(options, add, uses == 0 ? 
                    SELECTION(ID_WAGONS_INFO_MENU_DELETE, "Delete") :
                    option_separator()
                            ->name(format("Delete (%d uses)", uses))
                            ->build()
    );
    mcall(options, add, SELECTION(ID_WAGONS_INFO_MENU_COUPLE, "Couple to train"));
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

override
menu wagons_couple_menu(wagon w) {
    int index = find_wagon(w->id);

    option_array options = new(option_array);
    mcall(options, add, option_separator()
                    ->id(index)
                    ->name(w->id)
                    ->build());
    mcall(options, add, SEPARATOR);
    for (int i = 0; i < trains->length; i++) {
        train t = mcall(trains, get, i);
        mcall(options, add, SELECTION(i, t->id));
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, BACK);
    mcall(options, add, BACK_TO_MAIN_MENU);
    return new(vmenu, options);
}

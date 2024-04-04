#include "app.h"

impl_arraydef(app);

app launched_app = NULL;

constructor(app,
    string name,
    void function(launch, app a)
) {
    app obj = malloc(sizeoftype(app));
    obj->name = name;
    obj->launch = launch;
    return obj;
}

override
screen app_screen(void function(on_action, component c)) {
    screen s = mcall(render_stack, push, on_action);

    add_component(s, -1, title, new(title, launched_app->name));
    add_component(s, -1, separator, new(separator));

    return s;
}

override
screen prev_screen() {
    return mcall(render_stack->screens, get, render_stack->screens->length - 2);
}

override
menu prev_menu() {
    screen s = prev_screen();
    return mcall(s->components, get, 2)->data;
}

override
void remove_option_and_decrement_after(menu m, int start_id, string none_available_message) {
    if (m->options->length == 4) { // product, separator, back, main menu
        mcall(m->options, set, 0, option_separator()
                        ->name(none_available_message)
                        ->build());
    } else {
        int i = 0;
        for (; i < m->options->length - 3; i++) {
            option opt = mcall(m->options, get, i);
            if (opt->id == start_id) {
                mcall(m->options, remove, i);
                break;
            }
        }
        for (; i < m->options->length - 3; i++) {
            option o = mcall(m->options, get, i);
            o->id--;
        }
    }
}

void goto_screen_main_menu() {
    mcall(render_stack, pop_to, 2);
}

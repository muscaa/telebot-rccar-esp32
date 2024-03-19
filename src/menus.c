#include "menus.h"

#include "apps/apps.h"
#include "utils/screen/components.h"

private void on_input(component c) {
    if (c->id == 0) {
        //input d = c->data;
    } else if (c->id == -1) {
        mcall0(render_stack, pop);
    }
}

private void input_test() {
    screen s = mcall(render_stack, push, on_input);

    add_component(s, 0, input, new(input_builder, "Input Test: ")
            ->value("Value")
            ->max_length(10)
            ->accepts("az|AZ|09")
            ->build()
    );
    add_component(s, -1, trigger, new(trigger, "(ESC to go back)", K_ESCAPE));
}

private void on_action(component c) {
    if (c->id == 1) {
        menu d = c->data;

        option opt = mcall(d->options, get, d->current);

        if (opt->id != -1) {
            if (opt->id == 1) {
                input_test();
                return;
            }
            get_app(opt->id).launch();
        }

        mcall0(render_stack, pop);
    }
}

override
void main_menu() {
    screen s = mcall(render_stack, push, on_action);
    
    option_array options = new(option_array);
    mcall(options, add, SEPARATOR);
    for (int i = 0; i < get_apps_length(); i++) {
        app app = get_app(i);
        mcall(options, add, option_selection(app.name)
                            ->id(i)
                            ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, option_selection("Exit")
                        ->foreground_hover(COLOR_RED)
                        ->build());
    
    add_component(s, 0, title, new(title, "Main Menu"));
    add_component(s, 1, menu, new(vmenu, options));
}

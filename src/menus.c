#include "menus.h"

#include "apps/apps.h"

private void on_action(component c) {
    if (c->id == 0) {
        menu m = c->data;

        option opt = mcall(m->options, get, m->current);

        if (opt->id != -1) {
            println("launching %d", opt->id);
            get_app(opt->id).launch();
        }

        mcall0(render_stack, pop);
    }
}

override
void main_menu() {
    screen s = mcall(render_stack, push, on_action);
    
    option_array options = new(option_array);
    mcall(options, add, builder_title("Main Menu")
                    ->build());
    mcall(options, add, SEPARATOR);
    for (int i = 0; i < get_apps_length(); i++) {
        app app = get_app(i);
        mcall(options, add, builder_selection(app.name)
                            ->id(i)
                            ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, builder_selection("Exit")
                        ->foreground_hover(COLOR_RED)
                        ->build());
    
    add_component(menu, 0, s, new(vmenu, options));
}

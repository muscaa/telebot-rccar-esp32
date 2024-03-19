#include "screens.h"

#include "apps/apps.h"
#include "utils/screen/components.h"

private void on_action(component c) {
    if (c->id == 1) {
        menu d = c->data;
        option opt = mcall(d->options, get, d->current);

        if (opt->id != -1) {
            launch_app(opt->id);
            return;
        }

        mcall0(render_stack, pop);
    }
}

override
void screen_main_menu() {
    screen s = mcall(render_stack, push, on_action);
    
    option_array options = new(option_array);
    for (int i = 0; i < get_apps_length(); i++) {
        app app = get_app(i);
        mcall(options, add, option_selection(app->name)
                            ->id(i)
                            ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, option_selection("Exit")
                        ->foreground_hover(COLOR_RED)
                        ->build());
    
    add_component(s, 0, title, new(title, "Main Menu"));
    add_component(s, -1, separator, new(separator));
    add_component(s, 1, menu, new(vmenu, options));
}

#include "main_menu.h"

#include "../apps/apps.h"
#include "../accounts/accounts.h"

private void on_action(component c) {
    if (c->id != 1) return;

    menu m = c->data;
    option opt = mcall(m->options, get, m->current);

    switch (opt->id) {
        case -2: {
            mcall(render_stack, pop_to, 0);
            break;
        }
        case -3: {
            if (!accounts_logout()) break;

            mcall0(render_stack, pop);
            break;
        }
        case -4: {
            // TODO: Account settings action
            break;
        }
        default: {
            launch_app(opt->id);
        }
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
    /*mcall(options, add, option_selection("Account Settings")
                    ->id(-4)
                    ->build());*/
    mcall(options, add, option_selection("Logout")
                    ->id(-3)
                    ->foreground_hover(COLOR_RED)
                    ->build());
    mcall(options, add, option_selection("Exit")
                    ->id(-2)
                    ->foreground_hover(COLOR_RED)
                    ->build());
    
    add_component(s, 0, title, new(title, "Main Menu"));
    add_component(s, -1, separator, new(separator));
    add_component(s, 1, menu, new(vmenu, options));
}

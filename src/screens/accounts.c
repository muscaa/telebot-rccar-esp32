#include "accounts.h"

#include "../utils/utils.h"
#include "accounts_login.h"
#include "accounts_register.h"

private void on_action(component c) {
    if (c->id != 0) return;

    menu m = c->data;
    option opt = mcall(m->options, get, m->current);

    switch (opt->id) {
        case 0: {
            screen_login();
            break;
        }
        case 1: {
            screen_register();
            break;
        }
        case 2: {
            mcall0(render_stack, pop);
            break;
        }
    }
}

override
void screen_accounts() {
    screen s = mcall(render_stack, push, on_action);
    
    option_array options = new(option_array);
    mcall(options, add, option_selection("Login")
                    ->id(0)
                    ->build());
    mcall(options, add, option_selection("Register")
                    ->id(1)
                    ->build());
    mcall(options, add, SEPARATOR);
    mcall(options, add, option_selection("Exit")
                    ->id(2)
                    ->foreground_hover(COLOR_RED)
                    ->build());
    
    add_component(s, -1, title, new(title, "Accounts"));
    add_component(s, -1, separator, new(separator));
    add_component(s, 0, menu, new(vmenu, options));
}

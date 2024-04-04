#include "accounts_login.h"

#include "../accounts/accounts.h"
#include "main_menu.h"

private void username_input(screen s, int id) {
    insert_component(s, 0, -2 - id, label, new(label, "Username: "));
    insert_component(s, 0, id, input, new(input_builder)
                    ->max_length(32)
                    ->accepts("az|AZ|09|_")
                    ->build());
}

private void password_input(screen s, int id) {
    insert_component(s, 0, -2 - id, label, new(label, "Password: "));
    insert_component(s, 0, id, input, new(input_builder)
                    ->password()
                    ->max_length(48)
                    ->accepts(" ~")
                    ->build());
}

private void on_action(component c) {
    screen s = c->parent;

    switch (c->id) {
        case 0: {
            mcall0(render_stack, pop);
            break;
        }
        case 1: {
            password_input(s, 2);
            break;
        }
        case 2: {
            input username = mcall(s, get, 1)->data;
            input password = mcall(s, get, 2)->data;

            if (!accounts_login(username->result, password->result)) {
                println("");
                println("Invalid username or password!");
                system_exit(1);
                return;
            }
            
            mcall0(render_stack, pop);

            screen_main_menu();
            break;
        }
    }
}

override
void screen_login() {
    screen s = mcall(render_stack, push, on_action);
    
    add_component(s, -1, title, new(title, "Login"));
    add_component(s, -1, separator, new(separator));

    add_component(s, 0, trigger, new(trigger, K_ESCAPE));
    add_component(s, -1, separator, new(separator));
    add_component(s, -1, label, new(label, "(Press ESC to go back)"));

    username_input(s, 1);
}

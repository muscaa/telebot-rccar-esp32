#include "accounts_register.h"

#include "../accounts/accounts.h"

private void username_input(screen s, int id) {
    insert_component(s, 0, -2 - id, label, new(label, "Username: "));
    insert_component(s, 0, id, input, new(input_builder)
                    ->max_length(32)
                    ->accepts("az|AZ|09|_")
                    ->build());
}

private void password_input(screen s, int id, bool repeat) {
    insert_component(s, 0, -2 - id, label, new(label, repeat ? "Repeat Password: " : "Password: "));
    insert_component(s, 0, id, input, new(input_builder)
                    ->password()
                    ->max_length(48)
                    ->accepts(" ~")
                    ->build());
}

private void on_fail(screen s) {
    mcall(s, remove, 3); // pass2
    mcall(s, remove, -5); // pass2 label
    mcall(s, remove, 2); // pass1
    mcall(s, remove, -4); // pass1 label

    insert_component(s, 0, -7, separator, new(separator));
    insert_component(s, 0, -6, label, new(label, "Passwords do not match! Press ENTER to try again."));
    insert_component(s, 0, 4, trigger, new(trigger, K_RETURN));
    insert_component(s, 0, -8, separator, new(separator));
}

private void on_success(screen s, string username, string password) {
    if (!accounts_register(username, password)) {
        println("");
        println("Account already exists!");
        system_exit(1);
        return;
    }

    mcall0(render_stack, pop);
}

private void on_action(component c) {
    screen s = c->parent;

    switch (c->id) {
        case 0: {
            mcall0(render_stack, pop);
            break;
        }
        case 1: {
            password_input(s, 2, false);
            break;
        }
        case 2: {
            password_input(s, 3, true);
            break;
        }
        case 3: {
            input username = mcall(s, get, 1)->data;
            input pass1 = mcall(s, get, 2)->data;
            input pass2 = mcall(s, get, 3)->data;

            if (strcmp(pass1->result, pass2->result) != 0) {
                on_fail(s);
                return;
            }

            on_success(s, username->result, pass1->result);
            break;
        }
        case 4: {
            mcall(s, remove, -8); // trigger separator
            mcall(s, remove, 4); // trigger
            mcall(s, remove, -6); // trigger label
            mcall(s, remove, -7); // trigger separator

            password_input(s, 2, false);
            break;
        }
    }
}

override
void screen_register() {
    screen s = mcall(render_stack, push, on_action);
    
    add_component(s, -1, title, new(title, "Register"));
    add_component(s, -1, separator, new(separator));

    add_component(s, 0, trigger, new(trigger, K_ESCAPE));
    add_component(s, -1, separator, new(separator));
    add_component(s, -1, label, new(label, "(Press ESC to go back)"));

    username_input(s, 1);
}

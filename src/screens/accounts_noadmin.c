#include "accounts_noadmin.h"

#include "../accounts/accounts.h"

private void password_input(screen s, int id, bool repeat) {
    add_component(s, -2 - id, label, new(label, repeat ? "Repeat Admin Password: " : "Admin Password: "));
    add_component(s, id, input, new(input_builder)
                    ->password()
                    ->max_length(48)
                    ->accepts(" ~") // ascii from space to ~ means all characters
                    ->build());
}

private void on_fail(screen s) {
    mcall(s, remove, 1); // in1
    mcall(s, remove, -3); // in1 label
    mcall(s, remove, 0); // in0
    mcall(s, remove, -2); // in0 label

    add_component(s, -4, label, new(label, "Passwords do not match! Press ENTER to try again."));
    add_component(s, 2, trigger, new(trigger, K_RETURN));
}

private void on_success(screen s, string password) {
    if (!accounts_register("admin", password)) {
        println("Something went wrong!");
        system_exit(1);
        return;
    }

    mcall0(render_stack, pop);

    init_accounts();
}

private void on_action(component c) {
    screen s = c->parent;

    switch (c->id) {
        case 0: {
            password_input(s, 1, true);
            break;
        }
        case 1: {
            input in0 = mcall(s, get, 0)->data;
            input in1 = mcall(s, get, 1)->data;

            if (strcmp(in0->result, in1->result) != 0) {
                on_fail(s);
                return;
            }

            on_success(s, in0->result);
            break;
        }
        case 2: {
            mcall(s, remove, 2); // trigger
            mcall(s, remove, -4); // trigger label

            password_input(s, 0, false);
            break;
        }
    }
}

override
void screen_noadmin() {
    screen s = mcall(render_stack, push, on_action);

    add_component(s, -1, title, new(title, "Admin Account Setup"));
    add_component(s, -1, separator, new(separator));

    password_input(s, 0, false);
}

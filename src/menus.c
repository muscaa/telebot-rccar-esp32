#include "menus.h"

#include "utils/utils.h"
#include "apps/apps.h"

// PUBLIC
int main_menu() {
    clear_screen();

    int len = 0;
    option options[4 + get_apps_length()];
    options[len++] = new_option_builder()
                    .name("Main Menu")
                    .separator()
                    .build();
    options[len++] = new_option_builder()
                    .separator()
                    .build();
    for (int i = 0; i < get_apps_length(); i++) {
        app app = get_app(i);
        options[len++] = new_option_builder()
                        .id(i)
                        .name(app.name)
                        .build();
    }
    options[len++] = new_option_builder()
                    .separator()
                    .build();
    options[len++] = new_option_builder()
                    .name("Exit")
                    .foreground_hover(COLOR_RED)
                    .build();
    option opt = vmenu(len, options);

    if (opt.id != -1) get_app(opt.id).launch();

    return 0;
}
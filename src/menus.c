#include "menus.h"

#include "utils/utils.h"
#include "apps/apps.h"

// PUBLIC
int main_menu() {
    int len = 0;
    option options[4 + get_apps_length()];
    options[len++] = builder_title("Main Menu")
                    .build();
    options[len++] = SEPARATOR;
    for (int i = 0; i < get_apps_length(); i++) {
        app app = get_app(i);
        
        options[len++] = builder_selection(app.name)
                        .id(i)
                        .build();
    }
    options[len++] = builder_separator()
                    .build();
    options[len++] = builder_selection("Exit")
                    .foreground_hover(COLOR_RED)
                    .build();
    option opt = vmenu(len, options);

    if (opt.id != -1) get_app(opt.id).launch();

    return 0;
}
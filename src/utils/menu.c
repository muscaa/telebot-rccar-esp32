#include "menu.h"

// PUBLIC
option new_option(string name, string description, int color_code) {
    option opt;
    opt.name = name;
    opt.description = description;
    opt.color_code = color_code;
    return opt;
}

int vmenu(string title, int options_count, option options[]) {
    start_capture();
    int capture;
    int current = 0;
    bool redraw = true;
    while ((capture = read_capture()) != KEY_RETURN) {
        if (capture == KEY_UP) {
            current = (current - 1 + options_count) % options_count;
            redraw = true;
        } else if (capture == KEY_DOWN) {
            current = (current + 1) % options_count;
            redraw = true;
        }

        if (redraw) {
            clear_screen();

            printf("%s\n", title);
            printf("\n");

            for (int i = 0; i < options_count; i++) {
                option opt = options[i];
                
                if (i == current) {
                    push_foreground(opt.color_code);
                    printf("%s\n", opt.name);
                    pop_foreground();
                } else {
                    printf("%s\n", opt.name);
                }
            }

            redraw = false;
        }
    }
    stop_capture();
    return current;
}
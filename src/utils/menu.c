#include "menu.h"
#include "colors.h"
#include "console.h"
#include <stdlib.h>

// PRIVATE
void decrease(int* current, int options_count, option options[]) {
    do {
        *current = (*current - 1 + options_count) % options_count;
    } while (options[*current].separator);
}

void increase(int* current, int options_count, option options[]) {
    do {
        *current = (*current + 1) % options_count;
    } while (options[*current].separator);
}

option_builder set_id(int id);
option_builder set_name(string name);
option_builder set_description(string description);
option_builder set_hover_color(int hover_color);
option_builder set_separator(bool separator);
option_builder set_action(void (*action)());
option build_option();

option_builder ob = { set_id, set_name, set_description, set_hover_color, set_separator, set_action, build_option };
option current_building_option;

option_builder set_id(int id) {
    current_building_option.id = id;
    return ob;
}

option_builder set_name(string name) {
    current_building_option.name = name;
    return ob;
}

option_builder set_description(string description) {
    current_building_option.description = description;
    return ob;
}

option_builder set_hover_color(int hover_color) {
    current_building_option.hover_color = hover_color;
    return ob;
}

option_builder set_separator(bool separator) {
    current_building_option.separator = separator;
    return ob;
}

option_builder set_action(void (*action)()) {
    current_building_option.action = action;
    return ob;
}

option build_option() {
    return current_building_option;
}

// PUBLIC
option new_option() {
    option opt = {
        -1,
        NULL,
        NULL,
        COLOR_BLUE,
        false,
        NULL,
        -1
    };
    return opt;
}

option_builder new_option_builder() {
    current_building_option = new_option();
    return ob;
}

option vmenu(int options_count, option options[]) {
    start_capture();
    int current = -1;
    increase(&current, options_count, options);
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == K_UP) {
            decrease(&current, options_count, options);
            redraw = true;
        } else if (capture == K_DOWN) {
            increase(&current, options_count, options);
            redraw = true;
        }

        if (redraw) {
            clear_screen();

            //println("%s", title);
            //println("");

            for (int i = 0; i < options_count; i++) {
                option opt = options[i];
                //opt.index = i; // not working? why? whatever..
                
                if (i == current) {
                    push_foreground(opt.hover_color);
                    println("%s", opt.name != NULL ? opt.name : "");
                    pop_foreground();
                } else {
                    println("%s", opt.name != NULL ? opt.name : "");
                }
            }

            redraw = false;

            string desc = options[current].description;
            if (desc != NULL) {
                //println("");
                //println("");
                println(desc);
            }
        }
    }
    stop_capture();

    option opt = options[current];
    opt.index = current; // fixed the index problem
    if (opt.action != NULL) opt.action(current);

    return opt;
}
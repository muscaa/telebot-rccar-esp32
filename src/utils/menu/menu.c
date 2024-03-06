#include "menu.h"

#include "../system/console.h"
#include "../system/colors.h"

// PRIVATE
void decrease(int* current, const int options_length, option options[]) {
    do {
        *current = (*current - 1 + options_length) % options_length;
    } while (options[*current].separator);
}

void increase(int* current, const int options_length, option options[]) {
    do {
        *current = (*current + 1) % options_length;
    } while (options[*current].separator);
}

option_builder set_id(int id);
option_builder set_name(string name);
option_builder set_name_hover(string name_hover);
option_builder set_description(string description);
option_builder set_foreground(int foreground);
option_builder set_foreground_hover(int foreground);
option_builder set_background(int background);
option_builder set_background_hover(int background);
option_builder set_separator();
option_builder set_action(void (*action)());
option build_option();

option_builder ob = {
    set_id,
    set_name,
    set_name_hover,
    set_description,
    set_foreground,
    set_foreground_hover,
    set_background,
    set_background_hover,
    set_separator,
    set_action,
    build_option
};
option current_building_option;

option_builder set_id(int id) {
    current_building_option.id = id;
    return ob;
}

option_builder set_name(string name) {
    current_building_option.name = name;
    return ob;
}

option_builder set_name_hover(string name_hover) {
    current_building_option.name_hover = name_hover;
    return ob;
}

option_builder set_description(string description) {
    current_building_option.description = description;
    return ob;
}

option_builder set_foreground(int foreground) {
    current_building_option.foreground = foreground;
    return ob;
}

option_builder set_foreground_hover(int foreground_hover) {
    current_building_option.foreground_hover = foreground_hover;
    return ob;
}

option_builder set_background(int background) {
    current_building_option.background = background;
    return ob;
}

option_builder set_background_hover(int background_hover) {
    current_building_option.background_hover = background_hover;
    return ob;
}

option_builder set_separator() {
    current_building_option.separator = true;
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
        -1,
        NULL,
        NULL,
        NULL,
        COLOR_WHITE, // if not set, the system overrides it
        COLOR_BLUE,
        -1,
        -1,
        false,
        NULL
    };
    return opt;
}

option_builder new_option_builder() {
    current_building_option = new_option();
    return ob;
}

string get_option_name(option opt, bool hovered, int* background, int* foreground) {
    *background = -1;
    *foreground = -1;
    if (opt.background != -1) *background = opt.background;
    if (opt.foreground != -1) *foreground = opt.foreground;

    string name = "";
    if (opt.name != NULL) name = opt.name;

    if (hovered) {
        if (opt.background_hover != -1) *background = opt.background_hover;
        if (opt.foreground_hover != -1) *foreground = opt.foreground_hover;

        if (opt.name_hover != NULL) name = opt.name_hover;
    }

    return name;
}

void menu_pre_draw() {
    clear_screen();
}

option menu(const int options_length, option options[], const int increase_key, const int decrease_key,
                void (*pre_draw)(), void (*draw)(int, option[], int, int), void (*post_draw)(int, option[], int)) {
    start_capture();
    int current = -1;
    increase(&current, options_length, options);
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN) {
        if (capture == increase_key) {
            increase(&current, options_length, options);
            redraw = true;
        } else if (capture == decrease_key) {
            decrease(&current, options_length, options);
            redraw = true;
        }

        if (redraw) {
            redraw = false;

            pre_draw();
            for (int i = 0; i < options_length; i++) {
                draw(options_length, options, current, i);
            }
            post_draw(options_length, options, current);
        }
    }
    stop_capture();

    option opt = options[current];
    opt.index = current;
    if (opt.action != NULL) opt.action(current);

    return opt;
}

// vertical menu start
void vmenu_draw(const int options_length, option options[], int current, int i) {
    option opt = options[i];
    
    int background;
    int foreground;
    string name = get_option_name(opt, current == i, &background, &foreground);

    if (background != -1) push_background(background);
    if (foreground != -1) push_foreground(foreground);

    println(name);

    if (foreground != -1) pop_foreground();
    if (background != -1) pop_background();
}

void vmenu_post_draw(const int options_length, option options[], int current) {
    string desc = options[current].description;
    if (desc != NULL) {
        println(desc);
    }
}

option vmenu(const int options_length, option options[]) {
    return menu(options_length, options, K_DOWN, K_UP, menu_pre_draw, vmenu_draw, vmenu_post_draw);
}
// vertical menu end

// horizontal menu start
void hmenu_draw(const int options_length, option options[], int current, int i) {
    option opt = options[i];
    
    int background;
    int foreground;
    string name = get_option_name(opt, current == i, &background, &foreground);

    if (background != -1) push_background(background);
    if (foreground != -1) push_foreground(foreground);

    print(name);

    if (foreground != -1) pop_foreground();
    if (background != -1) pop_background();
}

void hmenu_post_draw(const int options_length, option options[], int current) {
    string desc = options[current].description;
    if (desc != NULL) {
        print(desc);
    }

    println("");
}

option hmenu(const int options_length, option options[]) {
    return menu(options_length, options, K_RIGHT, K_LEFT, menu_pre_draw, hmenu_draw, hmenu_post_draw);
}
// horizontal menu end
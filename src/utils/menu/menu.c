#include "menu.h"

#include "../system/console.h"
#include "../system/colors.h"

private void decrease(int* current, const int options_length, option options[]) {
    do {
        *current = (*current - 1 + options_length) % options_length;
    } while (options[*current].separator);
}

private void increase(int* current, const int options_length, option options[]) {
    do {
        *current = (*current + 1) % options_length;
    } while (options[*current].separator);
}

private option_builder set_id(int id);
private option_builder set_name(string name);
private option_builder set_name_hover(string name_hover);
private option_builder set_description(string description);
private option_builder set_foreground(int foreground);
private option_builder set_foreground_hover(int foreground);
private option_builder set_background(int background);
private option_builder set_background_hover(int background);
private option_builder set_separator();
private option_builder set_action(void function(action));
private option build_option();

private option_builder builder = {
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
private option building;

private option_builder set_id(int id) {
    building.id = id;
    return builder;
}

private option_builder set_name(string name) {
    building.name = name;
    return builder;
}

private option_builder set_name_hover(string name_hover) {
    building.name_hover = name_hover;
    return builder;
}

private option_builder set_description(string description) {
    building.description = description;
    return builder;
}

private option_builder set_foreground(int foreground) {
    building.foreground = foreground;
    return builder;
}

private option_builder set_foreground_hover(int foreground_hover) {
    building.foreground_hover = foreground_hover;
    return builder;
}

private option_builder set_background(int background) {
    building.background = background;
    return builder;
}

private option_builder set_background_hover(int background_hover) {
    building.background_hover = background_hover;
    return builder;
}

private option_builder set_separator() {
    building.separator = true;
    return builder;
}

private option_builder set_action(void function(action)) {
    building.action = action;
    return builder;
}

private option build_option() {
    return building;
}

override
option new_option() {
    return (option) {
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
}

override
option_builder new_option_builder() {
    building = new_option();
    return builder;
}

private string get_option_name(option opt, bool hovered, int* background, int* foreground) {
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

private void menu_pre_draw() {
    clear_screen();
}

override
option menu(const int options_length, option options[], const int increase_key, const int decrease_key,
                void function(pre_draw), void function(draw, int, option[], int, int), void function(post_draw, int, option[], int)) {
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

private void vmenu_draw(const int options_length, option options[], int current, int i) {
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

private void vmenu_post_draw(const int options_length, option options[], int current) {
    string desc = options[current].description;
    if (desc != NULL) {
        println(desc);
    }
}

override
option vmenu(const int options_length, option options[]) {
    return menu(options_length, options, K_DOWN, K_UP, menu_pre_draw, vmenu_draw, vmenu_post_draw);
}

private void hmenu_draw(const int options_length, option options[], int current, int i) {
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

private void hmenu_post_draw(const int options_length, option options[], int current) {
    string desc = options[current].description;
    if (desc != NULL) {
        print(desc);
    }

    println("");
}

override
option hmenu(const int options_length, option options[]) {
    return menu(options_length, options, K_RIGHT, K_LEFT, menu_pre_draw, hmenu_draw, hmenu_post_draw);
}
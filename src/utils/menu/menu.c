#include "menu.h"

#include "../system/console.h"
#include "../system/colors.h"
#include <stdlib.h>

private option_builder impl_function(option_builder, id, int v);
private option_builder impl_function(option_builder, name, string v);
private option_builder impl_function(option_builder, name_hover, string v);
private option_builder impl_function(option_builder, description, string v);
private option_builder impl_function(option_builder, foreground, int v);
private option_builder impl_function(option_builder, foreground_hover, int v);
private option_builder impl_function(option_builder, background, int v);
private option_builder impl_function(option_builder, background_hover, int v);
private option_builder impl_function(option_builder, separator);
private option_builder impl_function(option_builder, on_action, void function(action, int));
private option impl_function(option_builder, build);

private option_builder builder;
private option building;

private option_builder impl_function(option_builder, id, int v) {
    building->id = v;
    return builder;
}

private option_builder impl_function(option_builder, name, string v) {
    building->name = v;
    return builder;
}

private option_builder impl_function(option_builder, name_hover, string v) {
    building->name_hover = v;
    return builder;
}

private option_builder impl_function(option_builder, description, string v) {
    building->description = v;
    return builder;
}

private option_builder impl_function(option_builder, foreground, int v) {
    building->foreground = v;
    return builder;
}

private option_builder impl_function(option_builder, foreground_hover, int v) {
    building->foreground_hover = v;
    return builder;
}

private option_builder impl_function(option_builder, background, int v) {
    building->background = v;
    return builder;
}

private option_builder impl_function(option_builder, background_hover, int v) {
    building->background_hover = v;
    return builder;
}

private option_builder impl_function(option_builder, separator) {
    building->separator = true;
    return builder;
}

private option_builder impl_function(option_builder, on_action, void function(action, int)) {
    building->action = action;
    return builder;
}

private option impl_function(option_builder, build) {
    return building;
}

constructor(option) {
    option obj = malloc(sizeof(struct __option));
    obj->id = -1;
    obj->index = -1;
    obj->name = NULL;
    obj->name_hover = NULL;
    obj->description = NULL;
    obj->foreground = COLOR_WHITE;
    obj->foreground_hover = COLOR_BLUE;
    obj->background = COLOR_UNDEFINED;
    obj->background_hover = COLOR_UNDEFINED;
    obj->separator = false;
    obj->action = NULL;
    return obj;
}

constructor(option_builder) {
    building = new(option);
    builder = malloc(sizeof(struct __option_builder));
    set_impl(option_builder, builder, id);
    set_impl(option_builder, builder, name);
    set_impl(option_builder, builder, name_hover);
    set_impl(option_builder, builder, description);
    set_impl(option_builder, builder, foreground);
    set_impl(option_builder, builder, foreground_hover);
    set_impl(option_builder, builder, background);
    set_impl(option_builder, builder, background_hover);
    set_impl(option_builder, builder, separator);
    set_impl(option_builder, builder, on_action);
    set_impl(option_builder, builder, build);
    return builder;
}

private void decrease(int* current, const int options_length, option options[]) {
    do {
        *current = (*current - 1 + options_length) % options_length;
    } while (options[*current]->separator);
}

private void increase(int* current, const int options_length, option options[]) {
    do {
        *current = (*current + 1) % options_length;
    } while (options[*current]->separator);
}

private string get_option_name(option opt, bool hovered, int* background, int* foreground) {
    *background = COLOR_UNDEFINED;
    *foreground = COLOR_UNDEFINED;
    if (opt->background != COLOR_UNDEFINED) *background = opt->background;
    if (opt->foreground != COLOR_UNDEFINED) *foreground = opt->foreground;

    string name = "";
    if (opt->name != NULL) name = opt->name;

    if (hovered) {
        if (opt->background_hover != COLOR_UNDEFINED) *background = opt->background_hover;
        if (opt->foreground_hover != COLOR_UNDEFINED) *foreground = opt->foreground_hover;

        if (opt->name_hover != NULL) name = opt->name_hover;
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
    opt->index = current;
    if (opt->action != NULL) opt->action(current);

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
    string desc = options[current]->description;
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
    string desc = options[current]->description;
    if (desc != NULL) {
        print(desc);
    }

    println("");
}

override
option hmenu(const int options_length, option options[]) {
    return menu(options_length, options, K_RIGHT, K_LEFT, menu_pre_draw, hmenu_draw, hmenu_post_draw);
}

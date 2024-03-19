#include "menu_option.h"

impl_arraydef(option);

constructor(option) {
    option obj = malloc(sizeoftype(option));
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

private option_builder builder = NULL;
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

constructor(option_builder) {
    building = new(option);
    if (builder == NULL) {
        builder = malloc(sizeoftype(option_builder));
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
    }
    return builder;
}

override
option_builder option_title(string title) {
    return new_option_builder()
            ->name(format(">>>  %s  <<<", title))
            ->separator()
            ;
}

override
option_builder option_separator() {
    return new_option_builder()
            ->separator()
            ;
}

override
option_builder option_selection(string name) {
    return new_option_builder()
            ->name(concat(" ", name))
            ->name_hover(concat("> ", name))
            ;
}

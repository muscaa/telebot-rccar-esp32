#include "menu.h"

private void decrease(int* current, option_array options) {
    do {
        *current = (*current - 1 + options->length) % options->length;
    } while (mcall(options, get, *current)->separator);
}

private void increase(int* current, option_array options) {
    do {
        *current = (*current + 1) % options->length;
    } while (mcall(options, get, *current)->separator);
}

private string option_name(option opt, bool hovered, int* background, int* foreground) {
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

private void post_render(screen s, option_array options, int current) {
    string desc = mcall(options, get, current)->description;
    if (desc != NULL) {
        mcall(s, append, desc);
        mcall0(s, new_line);
    }
}

private void hrender(screen s, option_array options, int current, int i) {
    option opt = mcall(options, get, i);
    
    int background;
    int foreground;
    string name = option_name(opt, current == i, &background, &foreground);

    if (background != COLOR_UNDEFINED) mcall(s, push_background, background);
    if (foreground != COLOR_UNDEFINED) mcall(s, push_foreground, foreground);

    mcall(s, append, name);

    if (foreground != COLOR_UNDEFINED) mcall0(s, pop_foreground);
    if (background != COLOR_UNDEFINED) mcall0(s, pop_background);
}

private void vrender(screen s, option_array options, int current, int i) {
    hrender(s, options, current, i);

    mcall0(s, new_line);
}

impl_init(menu) {
    menu d = obj->data;
    if (mcall(d->options, get, d->current)->separator) {
        increase(&d->current, d->options);
    }
}

impl_render(menu) {
    menu d = obj->data;

    for (int i = 0; i < d->options->length; i++) {
        vrender(obj->parent, d->options, d->current, i); // TODO hrender
    }
    post_render(obj->parent, d->options, d->current);
}

impl_key_event(menu) {
    if (consumed) return false;

    menu d = obj->data;

    if (key == K_RETURN) {
        call_action(obj);
        return true;
    } else if (key == d->increase_key) {
        increase(&d->current, d->options);
        mcall0(render_stack, refresh);
        return true;
    } else if (key == d->decrease_key) {
        decrease(&d->current, d->options);
        mcall0(render_stack, refresh);
        return true;
    }

    return false;
}

destructor(menu) {
    for (int i = 0; i < obj->options->length; i++) {
        free(mcall(obj->options, get, i));
    }
    delete(obj->options);
}

impl_component_methods(menu);
constructor(menu,
    const int increase_key,
    const int decrease_key,
    option_array options
) {
    menu obj = malloc(sizeoftype(menu));
    obj->increase_key = increase_key;
    obj->decrease_key = decrease_key;
    obj->options = options;
    obj->current = 0;
    set_component_methods(menu, obj);
    return obj;
}

menu construct(hmenu, option_array options) {
    return new(menu,
        K_RIGHT,
        K_LEFT,
        options
    );
}

menu construct(vmenu, option_array options) {
    return new(menu,
        K_DOWN,
        K_UP,
        options
    );
}

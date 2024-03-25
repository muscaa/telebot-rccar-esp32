#include "input.h"

impl_arraydef(input_filter);

impl_init(input) {
    input d = obj->data;
    d->result = malloc(d->max_length + 1);
    d->result[0] = '\0';
    if (d->default_value != NULL) {
        memcpy(d->result, d->default_value, strlen(d->default_value) + 1);
    }
}

impl_render(input) {
    screen s = obj->parent;
    input d = obj->data;

    bool exists = d->value_exists != NULL && d->value_exists(d->result);

    mcall(s, push_foreground, exists ? COLOR_RED : COLOR_BLUE);
    mcall(s, append, d->result);
    mcall0(s, pop_foreground);
    mcall0(s, new_line);
}

impl_key_event(input) {
    if (consumed) return false;

    input d = obj->data;

    int len = strlen(d->result);
    bool exists = d->value_exists != NULL && d->value_exists(d->result);

    if (key == K_RETURN && (len > 0 || d->allow_empty) && !exists) {
        d->result = realloc(d->result, len + 1);
        call_action(obj);
        return true;
    } else if (len > 0 && key == K_BACKSPACE) {
        d->result[--len] = '\0';
        mcall0(render_stack, refresh);
        return true;
    } else if (len < d->max_length) {
        for (int i = 0; i < d->filters->length; i++) {
            input_filter filter = mcall(d->filters, get, i);

            if (filter.to == 0) {
                if (key != filter.from) continue;
            } else if (key < filter.from || key > filter.to) continue;

            d->result[len++] = key;
            d->result[len] = '\0';
            
            mcall0(render_stack, refresh);
            return true;
        }
    }

    return false;
}

destructor(input) {

}

impl_create_component(input);
constructor(input) {
    input obj = malloc(sizeoftype(input));
    obj->default_value = NULL;
    obj->value_exists = NULL;
    obj->max_length = 0;
    obj->allow_empty = false;
    obj->filters = new(input_filter_array);
    obj->result = NULL;
    set_impl(input, obj, __destruct);
    return obj;
}

private input_builder builder = NULL;
private input building;

private input_builder impl_function(input_builder, value, string default_value) {
    building->default_value = default_value;
    return builder;
}

private input_builder impl_function(input_builder, exists, bool function(value_exists, string value)) {
    building->value_exists = value_exists;
    return builder;
}

private input_builder impl_function(input_builder, max_length, int max_length) {
    building->max_length = max_length;
    return builder;
}

private input_builder impl_function(input_builder, allow_empty) {
    building->allow_empty = true;
    return builder;
}

private input_builder impl_function(input_builder, accepts, string chars) {
    for (int i = 0; i < strlen(chars); i += 2) {
        char from = chars[i];
        char to = chars[i + 1] != '|' ? chars[++i] : 0;

        mcall(building->filters, add, (input_filter) { from, to });
    }
    return builder;
}

private input impl_function(input_builder, build) {
    return building;
}

constructor(input_builder) {
    building = new(input);
    if (builder == NULL) {
        builder = malloc(sizeoftype(input_builder));
        set_impl(input_builder, builder, value);
        set_impl(input_builder, builder, exists);
        set_impl(input_builder, builder, max_length);
        set_impl(input_builder, builder, allow_empty);
        set_impl(input_builder, builder, accepts);
        set_impl(input_builder, builder, build);
    }
    return builder;
}

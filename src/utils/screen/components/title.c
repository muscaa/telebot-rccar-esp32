#include "title.h"
#include <stdlib.h>

impl_init(title) {
    title d = obj->data;

    d->value = format(">>>  %s  <<<", d->value);
}

impl_render(title) {
    screen s = obj->parent;
    title d = obj->data;

    mcall(s, append, d->value);
    mcall0(s, new_line);
}

impl_key_event(title) {
    return false;
}

destructor(title) {
    free(obj->value);
}

impl_create_component(title);
constructor(title,
    string value
) {
    title obj = malloc(sizeoftype(title));
    obj->value = value;
    set_impl(title, obj, __destruct);
    return obj;
}

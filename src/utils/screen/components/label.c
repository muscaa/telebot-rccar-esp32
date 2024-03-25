#include "label.h"

impl_init(label) {}

impl_render(label) {
    screen s = obj->parent;
    label d = obj->data;

    mcall(s, append, d->text);
}

impl_key_event(label) {
    return false;
}

destructor(label) {}

impl_create_component(label);
constructor(label,
    string text
) {
    label obj = malloc(sizeoftype(label));
    obj->text = text;
    set_impl(label, obj, __destruct);
    return obj;
}

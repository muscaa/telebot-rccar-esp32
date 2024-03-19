#include "trigger.h"

impl_init(trigger) {}

impl_render(trigger) {
    screen s = obj->parent;
    trigger d = obj->data;

    mcall(s, append, d->label);
    mcall0(s, new_line);
}

impl_key_event(trigger) {
    if (consumed) return false;

    trigger d = obj->data;

    if (key == d->key) {
        call_action(obj);
        return true;
    }
    return false;
}

destructor(trigger) {}

impl_create_component(trigger);
constructor(trigger,
    string label,
    int key
) {
    trigger obj = malloc(sizeoftype(trigger));
    obj->label = label;
    obj->key = key;
    set_impl(trigger, obj, __destruct);
    return obj;
}

#include "trigger.h"

impl_init(trigger) {}

impl_render(trigger) {}

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
    int key
) {
    trigger obj = malloc(sizeoftype(trigger));
    obj->key = key;
    set_impl(trigger, obj, __destruct);
    return obj;
}

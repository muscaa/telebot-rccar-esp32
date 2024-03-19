#include "separator.h"

impl_init(separator) {}

impl_render(separator) {
    mcall0(obj->parent, new_line);
}

impl_key_event(separator) {
    return false;
}

destructor(separator) {}

impl_create_component(separator);
constructor(separator) {
    separator obj = malloc(sizeoftype(separator));
    set_impl(separator, obj, __destruct);
    return obj;
}

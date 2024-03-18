#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../defines.h"
#include "../array/array.h"
#include "../types/string.h"
#include "../system/system.h"
#include "../system/console.h"
#include "../system/colors.h"
#include "screen.h"

#define impl_init(type_name) private void impl_method0(component, init_##type_name)
#define impl_render(type_name) private void impl_method0(component, render_##type_name)
#define impl_key_event(type_name) private bool impl_method(component, key_event_##type_name, int key, bool consumed)
#define impl_component_methods(type_name) \
    private void impl_method0(component, __destruct_##type_name) { \
        type_name d = obj->data; \
        delete(d); \
    } \
    private component impl_method(type_name, create_component, int id) { \
        return new(component, \
                id, \
                obj, \
                get_impl(component, init_##type_name), \
                get_impl(component, render_##type_name), \
                get_impl(component, key_event_##type_name), \
                get_impl(component, __destruct_##type_name) \
        ); \
    }

#define component_methods(type_name) \
    component method(type_name, create_component, int id); \
    destruct(type_name);
#define set_component_methods(type_name, obj) \
    set_impl(type_name, obj, create_component); \
    set_impl(type_name, obj, __destruct)

#define call_action(obj) obj->parent->on_action(obj)

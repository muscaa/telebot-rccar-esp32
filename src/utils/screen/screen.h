#pragma once

#include "../defines.h"
#include "../array/array.h"
#include "../types/string.h"
#include "../system/console.h"
#include "../system/system.h"

type(screen);

abstract type(component,
    int id,
    void* data,
    void method0(component, init),
    void method0(component, render),
    bool method(component, key_event, int key, bool consumed),
    destruct(component)
) {
    int id;
    void* data;
    screen parent;

    abstract void method0(component, init);
    abstract void method0(component, render);
    abstract bool method(component, key_event, int key, bool consumed);

    abstract destruct(component);
};

arraydef(component);

type(screen,
    void function(on_action, component c)
) {
    component_array components;
    void function(on_action, component c);

    void method0(screen, render);
    void method(screen, key_event, int key);

    void method(screen, add, component c);

    void method(screen, append, string line);
    void method0(screen, new_line);

    void method(screen, push_foreground, const int color_code);
    void method0(screen, pop_foreground);
    void method(screen, push_background, const int color_code);
    void method0(screen, pop_background);

    destruct(screen);
};

arraydef(screen);

type(screen_renderer) {
    screen_array screens;

    void method0(screen_renderer, tick);
    void method0(screen_renderer, refresh);

    screen method(screen_renderer, push, void function(on_action, component c));
    void method0(screen_renderer, pop);

    destruct(screen_renderer);
};

extern screen_renderer render_stack;

#include "screen.h"

#include "../system/colors.h"

impl_arraydef(component);
impl_arraydef(screen);

screen_renderer render_stack;

constructor(component,
    int id,
    void* data,
    void method0(component, init),
    void method0(component, render),
    bool method(component, key_event, int key, bool consumed),
    destruct(component)
) {
    component obj = malloc(sizeoftype(component));
    obj->id = id;
    obj->data = data;
    obj->init = init;
    obj->render = render;
    obj->key_event = key_event;
    obj->__destruct = __destruct;
    return obj;
}

private void impl_method(screen, init, component c) {
    c->parent = obj;
    mcall0(c, init);
}

private void impl_method0(screen, render) {
    for (int i = 0; i < obj->components->length; i++) {
        component c = mcall(obj->components, get, i);

        mcall0(c, render);
    }
}

private void impl_method(screen, key_event, int key) {
    bool consumed = false;
    for (int i = obj->components->length - 1; i >= 0; i--) {
        component c = mcall(obj->components, get, i);

        if (mcall(c, key_event, key, consumed)) {
            consumed = true;
        }
    }
}

private component impl_method(screen, get, int id) {
    for (int i = 0; i < obj->components->length; i++) {
        component c = mcall(obj->components, get, i);
        if (c->id == id) {
            return c;
        }
    }
    return NULL;
}

private void impl_method(screen, add, component c) {
    mcall(obj, init, c);
    mcall(obj->components, add, c);

    mcall0(render_stack, refresh);
}

private component impl_method(screen, remove, int id) {
    for (int i = 0; i < obj->components->length; i++) {
        component old = mcall(obj->components, get, i);
        if (old->id == id) {
            mcall0(render_stack, refresh);

            return mcall(obj->components, remove, i);
        }
    }
    return NULL;
}

private component impl_method(screen, replace, int id, component c) {
    for (int i = 0; i < obj->components->length; i++) {
        component old = mcall(obj->components, get, i);
        if (old->id == id) {
            mcall(obj, init, c);

            mcall0(render_stack, refresh);

            return mcall(obj->components, set, i, c);
        }
    }
    return NULL;
}

private void impl_method(screen, insert, int id, component c) {
    for (int i = 0; i < obj->components->length; i++) {
        component old = mcall(obj->components, get, i);
        if (old->id == id) {
            mcall(obj, init, c);
            mcall(obj->components, insert, i, c);

            mcall0(render_stack, refresh);
            break;
        }
    }
}

private void impl_method(screen, append, string line) {
    print(line);
}

private void impl_method0(screen, new_line) {
    println("");
}

private void impl_method(screen, push_foreground, const int color_code) {
    mcall(obj, append, push_foreground_noprint(color_code));
}

private void impl_method0(screen, pop_foreground) {
    mcall(obj, append, pop_foreground_noprint());
}

private void impl_method(screen, push_background, const int color_code) {
    mcall(obj, append, push_background_noprint(color_code));
}

private void impl_method0(screen, pop_background) {
    mcall(obj, append, pop_background_noprint());
}

destructor(screen) {
    for (int i = obj->components->length - 1; i >= 0; i--) {
        component c = mcall(obj->components, get, i);
        delete(c);
    }
    delete(obj->components);
}

constructor(screen,
    void function(on_action, component c)
) {
    screen obj = malloc(sizeoftype(screen));
    obj->components = new(component_array);
    obj->on_action = on_action;

    set_impl(screen, obj, init);
    set_impl(screen, obj, render);
    set_impl(screen, obj, key_event);

    set_impl(screen, obj, get);
    set_impl(screen, obj, add);
    set_impl(screen, obj, remove);
    set_impl(screen, obj, replace);
    set_impl(screen, obj, insert);

    set_impl(screen, obj, append);
    set_impl(screen, obj, new_line);

    set_impl(screen, obj, push_foreground);
    set_impl(screen, obj, pop_foreground);
    set_impl(screen, obj, push_background);
    set_impl(screen, obj, pop_background);

    set_impl(screen, obj, __destruct);
    return obj;
}

private bool render = true;

private void impl_method0(screen_renderer, tick) {
    start_capture();
    int capture;

    int screen_width;
    int screen_height;
    while (system_running() && obj->screens->length > 0) {
        get_screen_size(&screen_width, &screen_height);

        screen s = mcall(obj->screens, get, obj->screens->length - 1);

        if (render) {
            render = false;

            clear_screen();

            push_foreground(COLOR_WHITE);

            mcall0(s, render);

            pop_foreground();

            println(""); // flush
        }

        capture = read_capture();
        
        mcall(s, key_event, capture);

        for (int i = 0; i < obj->screens_to_delete->length; i++) {
            screen s = mcall(obj->screens_to_delete, get, i);
            delete(s);
        }
        mcall0(obj->screens_to_delete, clear);
    }
    stop_capture();
}

private void impl_method0(screen_renderer, refresh) {
    render = true;
}

private screen impl_method(screen_renderer, push, void function(on_action, component c)) {
    screen s = new(screen, on_action);
    mcall(obj->screens, add, s);

    mcall0(render_stack, refresh);
    
    return s;
}

private void impl_method0(screen_renderer, pop) {
    screen s = mcall(obj->screens, remove, obj->screens->length - 1);
    mcall(obj->screens_to_delete, add, s);

    mcall0(render_stack, refresh);
}

private void impl_method(screen_renderer, pop_to, int length) {
    for (int i = obj->screens->length; i > length; i--) {
        mcall0(obj, pop);
    }
}

destructor(screen_renderer) {
    for (int i = obj->screens->length - 1; i >= 0; i--) {
        screen s = mcall(obj->screens, get, i);
        delete(s);
    }
    delete(obj->screens);
}

constructor(screen_renderer) {
    screen_renderer obj = malloc(sizeoftype(screen_renderer));
    obj->screens = new(screen_array);
    obj->screens_to_delete = new(screen_array);
    set_impl(screen_renderer, obj, tick);
    set_impl(screen_renderer, obj, refresh);
    set_impl(screen_renderer, obj, push);
    set_impl(screen_renderer, obj, pop);
    set_impl(screen_renderer, obj, pop_to);
    set_impl(screen_renderer, obj, __destruct);
    return obj;
}

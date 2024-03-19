#include "app.h"

impl_arraydef(app);

app launched_app = NULL;

constructor(app,
    string name,
    void function(launch, app a)
) {
    app obj = malloc(sizeoftype(app));
    obj->name = name;
    obj->launch = launch;
    return obj;
}

override
screen app_screen(void function(on_action, component c)) {
    screen s = mcall(render_stack, push, on_action);

    add_component(s, -1, title, new(title, launched_app->name));
    add_component(s, -1, separator, new(separator));

    return s;
}

#pragma once

#include "../component.h"
#include "menu_option.h"

type(menu,
    const int increase_key,
    const int decrease_key,
    option_array options,
    void function(render, screen s, menu m, int i)
) {
    int increase_key;
    int decrease_key;
    option_array options;
    void function(render, screen s, menu m, int i);

    int current;

    destruct(menu);
};
create_component(menu);

menu construct(hmenu, option_array options);

menu construct(vmenu, option_array options);

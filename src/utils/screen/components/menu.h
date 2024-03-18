#pragma once

#include "../component.h"
#include "menu_option.h"

type(menu,
    const int increase_key,
    const int decrease_key,
    option_array options
) {
    int increase_key;
    int decrease_key;
    option_array options;

    int current;

    component_methods(menu);
};

menu construct(hmenu, option_array options);

menu construct(vmenu, option_array options);

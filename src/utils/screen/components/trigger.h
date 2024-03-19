#pragma once

#include "../component.h"

type(trigger,
    string label,
    int key
) {
    string label;
    int key;

    destruct(trigger);
};
create_component(trigger);

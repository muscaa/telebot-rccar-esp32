#pragma once

#include "../component.h"

type(trigger,
    int key
) {
    int key;

    destruct(trigger);
};
create_component(trigger);

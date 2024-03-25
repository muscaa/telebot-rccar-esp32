#pragma once

#include "../component.h"

type(label,
    string text
) {
    string text;

    destruct(label);
};
create_component(label);

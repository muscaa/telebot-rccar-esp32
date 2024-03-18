#pragma once

#include "components/menu.h"
#include "components/input.h"

#define add_component(type_name, id, screen, c) \
    type_name type_name##_##id = c; \
    component type_name##_##id##_component = mcall(type_name##_##id, create_component, id); \
    mcall(screen, add, type_name##_##id##_component)

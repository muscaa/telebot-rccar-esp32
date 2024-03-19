#pragma once

#include "components/menu.h"
#include "components/input.h"
#include "components/title.h"

#define add_component(screen, id, type_name, c) mcall(screen, add, create_component_##type_name(c, id))
#define remove_component(screen, id) mcall(screen, remove, id)
#define replace_component(screen, id, type_name, c) mcall(screen, replace, id, create_component_##type_name(c, id))

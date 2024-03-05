#pragma once

#include <stdbool.h>

#include "string.h"
#include "colors.h"
#include "console.h"

typedef struct {
    int id;
    string name;
    string description;
    int hover_color;
    bool separator;
    void (*action)(int);
    int index;
} option;

struct _option_builder;
typedef struct _option_builder option_builder;
struct _option_builder {
    option_builder (*id)(int);
    option_builder (*name)(string);
    option_builder (*description)(string);
    option_builder (*hover_color)(int);
    option_builder (*separator)(bool);
    option_builder (*on_action)(void (*action)(int));
    option (*build)();
};

option new_option();

option_builder new_option_builder();

option vmenu(int options_count, option options[]);
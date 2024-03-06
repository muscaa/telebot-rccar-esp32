#pragma once

#include <stdbool.h>

#include "../types/string.h"

typedef struct {
    int id;
    int index;
    string name;
    string name_hover;
    string description;
    int foreground;
    int foreground_hover;
    int background;
    int background_hover;
    bool separator;
    void (*action)(int);
} option;

struct _option_builder;
typedef struct _option_builder option_builder;
struct _option_builder {
    option_builder (*id)(int);
    option_builder (*name)(string);
    option_builder (*name_hover)(string);
    option_builder (*description)(string);
    option_builder (*foreground)(int);
    option_builder (*foreground_hover)(int);
    option_builder (*background)(int);
    option_builder (*background_hover)(int);
    option_builder (*separator)();
    option_builder (*on_action)(void (*action)(int));
    option (*build)();
};

option new_option();

option_builder new_option_builder();

option vmenu(int options_count, option options[]);

option hmenu(int options_count, option options[]);
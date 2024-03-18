#pragma once

#include <stdbool.h>

#include "../defines.h"
#include "../types/string.h"
#include "../system/console.h"

type(option) {
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
    void function(action, int);
};

arraydef(option);

type(option_builder) {
    option_builder function(id, int);
    option_builder function(name, string);
    option_builder function(name_hover, string);
    option_builder function(description, string);
    option_builder function(foreground, int);
    option_builder function(foreground_hover, int);
    option_builder function(background, int);
    option_builder function(background_hover, int);
    option_builder function(separator);
    option_builder function(on_action, void function(action, int));
    option function(build);
};

option menu(const int options_length, option options[], const int increase_key, const int decrease_key,
                void function(pre_draw), void function(draw, int, option[], int, int), void function(post_draw, int, option[], int));

option vmenu(const int options_length, option options[]);

option hmenu(const int options_length, option options[]);

type(menuu, const int increase_key, const int decrease_key, option_array options) {
    int increase_key;
    int decrease_key;
    option_array options;
    void function(pre_draw, screen s);
    void function(draw, screen s, option_array options, int current, int i);
    void function(post_draw, screen s, option_array options, int current);
    option method(menuu, show, screen s);
    destruct(menuu);
};

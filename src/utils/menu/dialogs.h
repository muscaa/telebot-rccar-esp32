#pragma once

#include <stdbool.h>

#include "../types/string.h"

typedef struct {
    char from;
    char to;
} char_input_filter;

typedef struct {
    string result;
    bool exists;
    const void* additional;
} dialog_input_info;

typedef struct {
    string default_value;
    bool (*value_exists)(string);
    int max_length;
    bool allow_empty;
    int filters_length;
    char_input_filter* filters;
    void (*draw)(dialog_input_info);
} dialog_input;

struct _dialog_input_builder;
typedef struct _dialog_input_builder dialog_input_builder;
struct _dialog_input_builder {
    dialog_input_builder (*value)(string);
    dialog_input_builder (*exists)(bool (*value_exists)(string));
    dialog_input_builder (*max_length)(int);
    dialog_input_builder (*allow_empty)();
    dialog_input_builder (*accepts)(string);
    dialog_input_builder (*draw)(void (*draw)(dialog_input_info));
    dialog_input (*build)();
};

dialog_input new_dialog_input();

dialog_input_builder new_dialog_input_builder();

string dialog_input_string(dialog_input input, const void* additional);
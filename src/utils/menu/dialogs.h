#pragma once

#include <stdbool.h>

#include "../defines.h"
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
    bool function(value_exists, string);
    int max_length;
    bool allow_empty;
    int filters_length;
    char_input_filter* filters;
    void function(draw, dialog_input_info);
} dialog_input;

struct _dialog_input_builder;
typedef struct _dialog_input_builder dialog_input_builder;
struct _dialog_input_builder {
    dialog_input_builder function(value, string);
    dialog_input_builder function(exists, bool function(value_exists, string));
    dialog_input_builder function(max_length, int);
    dialog_input_builder function(allow_empty);
    dialog_input_builder function(accepts, string);
    dialog_input_builder function(draw, void function(draw, dialog_input_info));
    dialog_input function(build);
};

dialog_input new_dialog_input();

dialog_input_builder new_dialog_input_builder();

string dialog_input_string(dialog_input input, const void* additional);
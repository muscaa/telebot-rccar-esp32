#pragma once

#include <stdbool.h>

#include "../types/string.h"

typedef struct {
    char from;
    char to;
} char_input_filter;

typedef struct {
    string default_value;
    bool (*value_exists)(string);
    int max_length;
    bool allow_empty;
    int filters_length;
    char_input_filter* filters;
    string_array prefix;
    string_array suffix;
} dialog_input;

struct _dialog_input_builder;
typedef struct _dialog_input_builder dialog_input_builder;
struct _dialog_input_builder {
    dialog_input_builder (*value)(string);
    dialog_input_builder (*exists)(bool (*value_exists)(string));
    dialog_input_builder (*max_length)(int);
    dialog_input_builder (*allow_empty)();
    dialog_input_builder (*allow_chars)(char, char);
    dialog_input_builder (*allow_char)(char);
    dialog_input_builder (*prefix)(string_array);
    dialog_input_builder (*suffix)(string_array);
    dialog_input (*build)();
};

dialog_input new_dialog_input();

dialog_input_builder new_dialog_input_builder();

string dialog_input_string(dialog_input input);
#pragma once

#include "../component.h"

typedef struct {
    char from;
    char to;
} input_filter;

arraydef(input_filter);

type(input,
    string name
) {
    string name;
    string default_value;
    bool function(value_exists, string);
    int max_length;
    bool allow_empty;
    input_filter_array filters;
    
    string result;

    destruct(input);
};
create_component(input);

type(input_builder,
    string name
) {
    input_builder function(value, string default_value);
    input_builder function(exists, bool function(value_exists, string value));
    input_builder function(max_length, int max_length);
    input_builder function(allow_empty);
    input_builder function(accepts, string chars);
    input function(build);
};

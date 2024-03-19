#pragma once

#include "../component.h"

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

#define SEPARATOR option_separator()->build()

option_builder option_title(string title);

option_builder option_separator();

option_builder option_selection(string name);

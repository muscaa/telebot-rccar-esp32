#pragma once

#include "menu.h"

#include "../defines.h"

#define SEPARATOR builder_separator()->build()

typedef struct {
    string name;
    int function(on_action);
} program_action; // easier that working with ids

program_action new_action(string name, int function(on_action));

option option_selection_action(program_action actions[], int* i);

int action_performed(program_action actions[], option opt);

option_builder builder_title(string title);

option_builder builder_separator();

option_builder builder_selection(string name);

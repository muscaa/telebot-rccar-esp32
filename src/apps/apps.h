#pragma once

#include "../utils/utils.h"

typedef struct {
    string name;
    int function(launch);
} app;

void init_apps();

int get_apps_length();

app get_app(int index);
#pragma once

#include "../utils/utils.h"

typedef struct {
    string name;
    int (*launch)();
} app;

void init_apps();

int get_apps_length();

app get_app(int index);
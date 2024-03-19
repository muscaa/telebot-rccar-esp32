#pragma once

#include "../utils/utils.h"

type(app,
    string name,
    void function(launch)
) {
    string name;
    void function(launch);
};

arraydef(app);

void init_apps();

int get_apps_length();

app get_app(int index);

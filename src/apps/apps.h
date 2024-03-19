#pragma once

#include "../utils/utils.h"
#include "app.h"

void init_apps();

int get_apps_length();

app get_app(int index);

void launch_app(int index);

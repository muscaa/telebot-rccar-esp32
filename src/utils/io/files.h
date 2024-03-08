#pragma once

#include <stdbool.h>

#include "../types/string.h"
#include "../system/system.h"

bool file_exists(string path);

bool file_create(string path);

string file_parent(string path);

bool dir_create(string path);
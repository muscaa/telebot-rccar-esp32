#pragma once

#include <stdbool.h>

#include "../types/string.h"
#include "../system/system.h"

bool file_exists(string path);

bool create_file(string path);

bool create_dirs(string path);
#ifndef _UTILS_MENU_H_
    #define _UTILS_MENU_H_

    #include <stdio.h>
    #include <stdbool.h>

    #include "string.h"
    #include "colors.h"
    #include "console.h"
#endif

typedef struct {
    string name;
    string description;
    int color_code;
} option;

option new_option(string name, string description, int color_code);

int vmenu(string title, int options_count, option options[]);
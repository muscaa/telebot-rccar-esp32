#include "dialogs.h"

#include <stdlib.h>
#include <string.h>

#include "../system/console.h"
#include "../system/colors.h"
#include "menu.h"

dialog_input_builder set_value(string default_value);
dialog_input_builder set_exists(bool (*value_exists)(string));
dialog_input_builder set_max_length(int max_length);
dialog_input_builder set_allow_empty();
dialog_input_builder set_allow_chars(char from, char to);
dialog_input_builder set_allow_char(char value);
dialog_input_builder set_prefix(string_array prefix);
dialog_input_builder set_suffix(string_array suffix);
dialog_input build_dialog_input();

dialog_input_builder builder = {
    set_value,
    set_exists,
    set_max_length,
    set_allow_empty,
    set_allow_chars,
    set_allow_char,
    set_prefix,
    set_suffix,
    build_dialog_input
};
dialog_input building;

dialog_input_builder set_value(string default_value) {
    building.default_value = default_value;
    return builder;
}

dialog_input_builder set_exists(bool (*value_exists)(string)) {
    building.value_exists = value_exists;
    return builder;
}

dialog_input_builder set_max_length(int max_length) {
    building.max_length = max_length;
    return builder;
}

dialog_input_builder set_allow_empty() {
    building.allow_empty = true;
    return builder;
}

dialog_input_builder set_allow_chars(char from, char to) {
    building.filters = realloc(building.filters, (building.filters_length + 1) * sizeof(char_input_filter));
    building.filters[building.filters_length++] = (char_input_filter) { from, to };
    return builder;
}

dialog_input_builder set_allow_char(char value) {
    return set_allow_chars(value, 0);
}

dialog_input_builder set_prefix(string_array prefix) {
    building.prefix = prefix;
    return builder;
}

dialog_input_builder set_suffix(string_array suffix) {
    building.suffix = suffix;
    return builder;
}

dialog_input build_dialog_input() {
    return building;
}

// PUBLIC
dialog_input new_dialog_input() {
    return (dialog_input) {
        NULL,
        NULL,
        0,
        false,
        0,
        malloc(sizeof(char_input_filter)),
        (string_array) { 0, NULL },
        (string_array) { 0, NULL }
    };
}

dialog_input_builder new_dialog_input_builder() {
    building = new_dialog_input();
    return builder;
}

string dialog_input_string(dialog_input input) {
    start_capture();
    int result_length = 0;
    char* result = malloc(input.max_length + 1);
    result[0] = '\0';
    if (input.default_value != NULL) {
        memcpy(result, input.default_value, strlen(input.default_value) + 1);
    }
    bool redraw = true;
    bool exists = false;
    int capture;
    while ((capture = read_capture()) != K_RETURN || (result_length == 0 && !input.allow_empty) || exists) {
        if (capture == K_ESCAPE) {
            stop_capture();
            free(result);
            return NULL;
        } else if (result_length > 0 && capture == K_BACKSPACE) {
            result[--result_length] = '\0';
            exists = input.value_exists != NULL && input.value_exists(result);
            redraw = true;
        } else if (result_length < input.max_length) {
            for (int i = 0; i < input.filters_length; i++) {
                char_input_filter filter = input.filters[i];

                if (filter.to == 0) {
                    if (capture == filter.from) {
                        result[result_length++] = capture;
                        result[result_length] = '\0';
                        exists = input.value_exists != NULL && input.value_exists(result);
                        redraw = true;
                        break;
                    }
                    continue;
                }

                if (capture >= filter.from && capture <= filter.to) {
                    result[result_length++] = capture;
                    result[result_length] = '\0';
                    exists = input.value_exists != NULL && input.value_exists(result);
                    redraw = true;
                    break;
                }
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            if (input.prefix.length != 0) {
                
            }

            println(TITLE.name);
            println("");
            print("Book title: ");
            push_foreground(exists ? COLOR_RED : COLOR_BLUE);
            println(result);
            pop_foreground();
            println("");
            println("(ESC to go back)");
        }
    }
    result = realloc(result, result_length + 1);
    stop_capture();
    return result;
}
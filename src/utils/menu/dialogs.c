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
dialog_input_builder set_accepts(string chars);
dialog_input_builder set_draw(void (*draw)(dialog_input_info));
dialog_input build_dialog_input();

dialog_input_builder builder_di = {
    set_value,
    set_exists,
    set_max_length,
    set_allow_empty,
    set_accepts,
    set_draw,
    build_dialog_input
};
dialog_input building_di;

dialog_input_builder set_value(string default_value) {
    building_di.default_value = default_value;
    return builder_di;
}

dialog_input_builder set_exists(bool (*value_exists)(string)) {
    building_di.value_exists = value_exists;
    return builder_di;
}

dialog_input_builder set_max_length(int max_length) {
    building_di.max_length = max_length;
    return builder_di;
}

dialog_input_builder set_allow_empty() {
    building_di.allow_empty = true;
    return builder_di;
}

dialog_input_builder set_accepts(string chars) { // az|AZ|-||
    for (int i = 0; i < strlen(chars); i += 2) {
        char from = chars[i];
        char to = chars[i + 1] != '|' ? chars[++i] : 0;
        
        building_di.filters = realloc(building_di.filters, (building_di.filters_length + 1) * sizeof(char_input_filter));
        building_di.filters[building_di.filters_length++] = (char_input_filter) { from, to };
    }
    return builder_di;
}

dialog_input_builder set_draw(void (*draw)(dialog_input_info)) {
    building_di.draw = draw;
    return builder_di;
}

dialog_input build_dialog_input() {
    return building_di;
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
        NULL
    };
}

dialog_input_builder new_dialog_input_builder() {
    building_di = new_dialog_input();
    return builder_di;
}

string dialog_input_string(dialog_input input, const void* additional) {
    start_capture();
    int result_length = 0;
    char* result = malloc(input.max_length + 1);
    result[0] = '\0';
    if (input.default_value != NULL) {
        result_length = strlen(input.default_value);
        memcpy(result, input.default_value, result_length + 1);
    }
    dialog_input_info info = { result, false, additional };
    bool redraw = true;
    int capture;
    while ((capture = read_capture()) != K_RETURN || (result_length == 0 && !input.allow_empty) || info.exists) {
        if (capture == K_ESCAPE) {
            free(result);
            stop_capture();
            return NULL;
        } else if (result_length > 0 && capture == K_BACKSPACE) {
            result[--result_length] = '\0';
            info.exists = input.value_exists != NULL && input.value_exists(result);
            redraw = true;
        } else if (result_length < input.max_length) {
            for (int i = 0; i < input.filters_length; i++) {
                char_input_filter filter = input.filters[i];

                if (filter.to == 0) {
                    if (capture != filter.from) continue;
                } else if (capture < filter.from || capture > filter.to) continue;

                result[result_length++] = capture;
                result[result_length] = '\0';
                info.exists = input.value_exists != NULL && input.value_exists(result);
                redraw = true;
                break;
            }
        }

        if (redraw) {
            redraw = false;

            clear_screen();

            if (input.draw != NULL) {
                info.result = result;
                input.draw(info);
            }
        }
    }
    result = realloc(result, result_length + 1);
    stop_capture();
    return result;
}
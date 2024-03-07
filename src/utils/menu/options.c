#include "options.h"

option_builder option_title(string title) {
    return new_option_builder()
            .name(concat(concat(">>>  ", title), "  <<<"))
            .separator()
            ;
}

option_builder option_separator() {
    return new_option_builder()
            .separator()
            ;
}

option_builder option_selection(string name) {
    return new_option_builder()
            .name(concat(" ", name))
            .name_hover(concat("> ", name))
            ;
}
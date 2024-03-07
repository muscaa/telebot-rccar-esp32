#include "options.h"

program_action new_action(string name, int (*on_action)()) {
    return (program_action) { name, on_action };
}

option option_selection_action(program_action actions[], int* i) {
    return builder_selection(actions[*i].name).id((*i)++).build();
}

int action_performed(program_action actions[], option opt) {
    return actions[opt.id].on_action();
}

option_builder builder_title(string title) {
    return new_option_builder()
            .name(concat(concat(">>>  ", title), "  <<<"))
            .separator()
            ;
}

option_builder builder_separator() {
    return new_option_builder()
            .separator()
            ;
}

option_builder builder_selection(string name) {
    return new_option_builder()
            .name(concat(" ", name))
            .name_hover(concat("> ", name))
            ;
}
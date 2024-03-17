#include "options.h"

override
program_action new_action(string name, int function(on_action)) {
    return (program_action) { name, on_action };
}

override
option option_selection_action(program_action actions[], int* i) {
    (*i)++; // weird compile warnings...
    return builder_selection(actions[*i - 1].name)->id(*i - 1)->build();
}

override
int action_performed(program_action actions[], option opt) {
    return actions[opt->id].on_action();
}

override
option_builder builder_title(string title) {
    return new_option_builder()
            ->name(concat(concat(">>>  ", title), "  <<<"))
            ->separator()
            ;
}

override
option_builder builder_separator() {
    return new_option_builder()
            ->separator()
            ;
}

override
option_builder builder_selection(string name) {
    return new_option_builder()
            ->name(concat(" ", name))
            ->name_hover(concat("> ", name))
            ;
}

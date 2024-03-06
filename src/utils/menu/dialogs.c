#include "dialogs.h"

bool dialog_yes_no(string title) {
    clear_screen();
    
    option options[] = {
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .name("yes")
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .name("no")
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
    };
    option opt = hmenu(sizeof(options) / sizeof(option), options);

}
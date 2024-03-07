#include "dialogs.h"

#include "../system/console.h"
#include "menu.h"

bool dialog_yes_no(string title) {
    clear_screen();

    option options[] = {
        new_option_builder()
                .name("################################\n#")
                .separator()
                .build(),
        new_option_builder()
                .name(title)
                .separator()
                .build(),
        new_option_builder()
                .name("\n################################\n\n")
                .separator()
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .id(0)
                .name("[yes]")
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .id(1)
                .name("[no]")
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .name("\n\n################################\n")
                .separator()
                .build(),
    };
    option opt = hmenu(sizeof(options) / sizeof(option), options);

    return opt.id == 0;
}
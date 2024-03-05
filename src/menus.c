#include "menus.h"
#include "p1/main.h"
#include "utils/console.h"
#include "utils/menu.h"

// PUBLIC
int main_menu() {
    clear_screen();

    option options[] = {
        new_option_builder()
                .name("Main Menu")
                .separator(true)
                .build(),
        new_option_builder()
                .separator(true)
                .build(),
        new_option_builder()
                .id(1)
                .name("#1. Meeting room reservation")
                .build(),
        new_option_builder()
                .id(2)
                .name("#2. System for keeping track of books in a library")
                .build(),
        new_option_builder()
                .id(3)
                .name("#3. Bicycle reservation system")
                .build(),
        new_option_builder()
                .id(4)
                .name("#4. System for booking pharmacy products")
                .build(),
        new_option_builder()
                .separator(true)
                .build(),
        new_option_builder()
                .name("Exit")
                .hover_color(COLOR_RED)
                .build(),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);

    switch (opt.id) {
        case 1: return p1_main();
        case 2: return p2_main();
        case 3: return p3_main();
        case 4: return p4_main();
    }
    return 0;
}
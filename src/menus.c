#include "menus.h"

// PRIVATE
void save_main_menu(config_writer w) {
    w.Long(123);
    w.Double(4.56);
    println("wrote some lines");
}

void load_main_menu(config_reader r) {
    long i = r.Long();
    double f = r.Double();
    println("read some lines");
    println("%d %lf", i, f);
}

// PUBLIC
int main_menu() {
    clear_screen();

    option options[] = {
        new_option_builder()
                .name("Main Menu")
                .separator()
                .build(),
        new_option_builder()
                .separator()
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
                .separator()
                .build(),
        new_option_builder()
                .name("Exit")
                .foreground_hover(COLOR_RED)
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
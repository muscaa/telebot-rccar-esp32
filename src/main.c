#include "apps/apps.h"
#include "menus.h"

int main() {
    push_foreground(COLOR_WHITE);
    init_apps();
    int exit = main_menu();
    pop_foreground();
    return exit;
}

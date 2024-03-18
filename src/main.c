#include "apps/apps.h"
#include "menus.h"

int main() {
    render_stack = new(screen_renderer);
    push_foreground(COLOR_WHITE);
    init_apps();
    int exit = main_menu();
    pop_foreground();
    delete(render_stack);
    return exit;
}

#include "apps/apps.h"
#include "screen_main_menu.h"

int main() {
    render_stack = new(screen_renderer);
    init_apps();

    main_menu();

    mcall0(render_stack, tick);

    delete(render_stack);
    return exit_code;
}

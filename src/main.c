#include "apps/apps.h"
#include "accounts/accounts.h"

int main() {
    render_stack = new(screen_renderer);

    init_accounts();
    init_apps();

    mcall0(render_stack, tick);

    delete(render_stack);
    return exit_code;
}

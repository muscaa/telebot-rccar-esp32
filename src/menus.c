#include "menus.h"

#include "apps/apps.h"

private string get_option_name(option opt, bool hovered, int* background, int* foreground) {
    *background = COLOR_UNDEFINED;
    *foreground = COLOR_UNDEFINED;
    if (opt->background != COLOR_UNDEFINED) *background = opt->background;
    if (opt->foreground != COLOR_UNDEFINED) *foreground = opt->foreground;

    string name = "";
    if (opt->name != NULL) name = opt->name;

    if (hovered) {
        if (opt->background_hover != COLOR_UNDEFINED) *background = opt->background_hover;
        if (opt->foreground_hover != COLOR_UNDEFINED) *foreground = opt->foreground_hover;

        if (opt->name_hover != NULL) name = opt->name_hover;
    }

    return name;
}

private void pre_draw(screen s) {

}

private void draw(screen s, option_array options, int current, int i) {
    option opt = mcall(options, get, i);
    
    int background;
    int foreground;
    string name = get_option_name(opt, current == i, &background, &foreground);

    if (background != COLOR_UNDEFINED) mcall(s, push_background, background);
    if (foreground != COLOR_UNDEFINED) mcall(s, push_foreground, foreground);

    mcall(s, append, name);

    if (foreground != COLOR_UNDEFINED) mcall0(s, pop_foreground);
    if (background != COLOR_UNDEFINED) mcall0(s, pop_background);

    mcall0(s, new_line);
}

private void post_draw(screen s, option_array options, int current) {
    string desc = mcall(options, get, current)->description;
    if (desc != NULL) {
        mcall(s, append, desc);
        mcall0(s, new_line);
    }
}

override
int main_menu() {
    screen s = mcall0(render_stack, push);
    
    option_array options = new(option_array);
    mcall(options, add, builder_title("Main Menu")
                    ->build());
    mcall(options, add, SEPARATOR);
    for (int i = 0; i < get_apps_length(); i++) {
        app app = get_app(i);
        mcall(options, add, builder_selection(app.name)
                            ->id(i)
                            ->build());
    }
    mcall(options, add, SEPARATOR);
    mcall(options, add, builder_selection("Exit")
                        ->foreground_hover(COLOR_RED)
                        ->build());
    
    menuu m = new(menuu, K_DOWN, K_UP, options);
    m->pre_draw = pre_draw;
    m->draw = draw;
    m->post_draw = post_draw;
    option opt = mcall(m, show, s);

    mcall0(render_stack, pop);

    if (opt->id != -1) get_app(opt->id).launch();

    return 0;
}

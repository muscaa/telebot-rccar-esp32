#pragma once

#include "../utils/utils.h"

#define SELECTION(option_name, option_id) option_selection(option_name)->id(option_id)->build()

#define ID_BACK -1
#define ID_BACK_TO_MAIN_MENU -2

#define BACK SELECTION("Back", ID_BACK)
#define BACK_TO_MAIN_MENU SELECTION("Back to Main Menu", ID_BACK_TO_MAIN_MENU)

#define MENU(menu_name, menu_id, cases) \
    private void menu_name##_menu_action(component c) { \
        if (c->id != menu_id) return; \
        \
        menu m = c->data; \
        option opt = mcall(m->options, get, m->current); \
        \
        switch (opt->id) { \
            case ID_BACK_TO_MAIN_MENU: \
            { \
                mcall(render_stack, pop_to, 1); \
                break; \
            } \
            case ID_BACK: \
            { \
                mcall0(render_stack, pop); \
                break; \
            } \
            cases \
        } \
    }

#define CASE(case_id, menu_name, menu_id) \
    case case_id: \
    { \
        screen menu_name##_menu_screen = app_screen(menu_name##_menu_action); \
        add_component(menu_name##_menu_screen, menu_id, menu, menu_name##_menu()); \
        break; \
    }

type(app,
    string name,
    void function(launch, app a)
) {
    string name;
    void function(launch, app a);
};

arraydef(app);

extern app launched_app;

screen app_screen(void function(on_action, component c));

#pragma once

#include "../utils/utils.h"

#define SELECTION(option_id, option_name) option_selection(option_name)->id(option_id)->build()

#define ID_BACK -2
#define ID_BACK_TO_MAIN_MENU -3

#define BACK SELECTION(ID_BACK, "Back")
#define BACK_TO_MAIN_MENU SELECTION(ID_BACK_TO_MAIN_MENU, "Back to Main Menu")

#define MENU_SCREEN(menu_name, menu_component) \
    screen menu_name##_menu_screen = app_screen(menu_name##_menu_action); \
    add_component(menu_name##_menu_screen, menu_name, menu, menu_component)

#define MENU(menu_name, cases, ...) \
    __VA_ARGS__ \
    private void menu_name##_menu_action(component c) { \
        if (c->id != menu_name) return; \
        \
        screen prev_screen = mcall(render_stack->screens, get, render_stack->screens->length - 2); \
        menu prev_menu = mcall(prev_screen->components, get, 2)->data; \
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

#define CASE(case_id, content) \
    case case_id: { \
        content \
        break; \
    }

#define CASE_MENU(case_id, menu_name) \
    CASE(case_id, \
        MENU_SCREEN(menu_name, menu_name##_menu()); \
    )

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

#pragma once

#include "../utils/utils.h"

#define SELECTION(option_name, option_id) option_selection(option_name)->id(option_id)->build()

#define ID_BACK -1
#define ID_BACK_TO_MAIN_MENU -2

#define BACK SELECTION("Back", ID_BACK)
#define BACK_TO_MAIN_MENU SELECTION("Back to Main Menu", ID_BACK_TO_MAIN_MENU)

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

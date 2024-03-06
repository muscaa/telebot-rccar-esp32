#include "apps.h"

#include "../menus.h"

#include "app1/main.h"
#include "app2/main.h"
#include "app3/main.h"
#include "app4/main.h"

#define MAX_APPS_LENGTH 4

int apps_length = 0;
app apps[MAX_APPS_LENGTH];

app new_app(string name, int (*launch)()) {
    app app = { name, launch };
    return app;
}

void init_apps() {
    apps[apps_length++] = new_app("Meeting rooms reservation system", app1_main);
    apps[apps_length++] = new_app("Library books tracking system", app2_main);
    apps[apps_length++] = new_app("Bicycle reservation system", app3_main);
    apps[apps_length++] = new_app("Pharmacy products booking system", app4_main);
}

int get_apps_length() {
    return apps_length;
}

app get_app(int index) {    
    return apps[index];
}
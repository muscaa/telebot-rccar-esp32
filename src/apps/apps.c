#include "apps.h"

#include "app1/main.h"
#include "app2/main.h"
#include "app3/main.h"
#include "app4/main.h"

#define MAX_APPS_LENGTH 4

private int apps_length = 0;
private app apps[MAX_APPS_LENGTH];

private app new_app(string name, int function(launch)) {
    return (app) { name, launch };
}

override
void init_apps() {
    apps[apps_length++] = new_app("Meeting rooms reservation system", app1_main);
    apps[apps_length++] = new_app("Library books tracking system", app2_main);
    apps[apps_length++] = new_app("Bicycle reservation system", app3_main);
    apps[apps_length++] = new_app("Pharmacy products booking system", app4_main);
}

override
int get_apps_length() {
    return apps_length;
}

override
app get_app(int index) {    
    return apps[index];
}
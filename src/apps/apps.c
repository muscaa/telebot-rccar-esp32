#include "apps.h"

#include "app1/appmain.h"
#include "app2/appmain.h"
#include "app3/appmain.h"
#include "app4/appmain.h"
#include "app5/appmain.h"

#define MAX_APPS_LENGTH 5

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
    apps[apps_length++] = new_app("Train wagons tracking system", app5_main);
}

override
int get_apps_length() {
    return apps_length;
}

override
app get_app(int index) {    
    return apps[index];
}

#include "apps.h"

#include "app.h"
#include "app1/appmain.h"
#include "app2/appmain.h"
#include "app3/appmain.h"
#include "app4/appmain.h"
#include "app5/appmain.h"

private app_array apps = NULL;

override
void init_apps() {
    if (apps != NULL) return;
    apps = new(app_array);

    mcall(apps, add, new(app, "Meeting rooms booking system", app1_main));
    mcall(apps, add, new(app, "Library books tracking system", app2_main));
    mcall(apps, add, new(app, "Bicycle reservation system", app3_main));
    mcall(apps, add, new(app, "Pharmacy products reservation system", app4_main));
    mcall(apps, add, new(app, "Train wagons tracking system", app5_main));
}

override
int get_apps_length() {
    return apps->length;
}

override
app get_app(int index) {
    return mcall(apps, get, index);
}

void launch_app(int index) {
    app a = get_app(index);

    launched_app = a;
    a->launch(a);
}

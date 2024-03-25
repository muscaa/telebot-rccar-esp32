#include "trains.h"
#include <stdlib.h>

#define CONFIG_FILE "app5/trains.dat"

impl_arraydef(wagon);
impl_arraydef(train);

wagon_array wagons;
wagon_array wagons_filtered;
string wagons_id_filter;
string wagons_type_filter;

train_array trains;

private void save_trains() {
    string parent = file_parent(CONFIG_FILE);
    if (parent != NULL) dir_create(parent);

    config_writer out = push_save_config(CONFIG_FILE);
    out.Int(wagons->length);
    for (int i = 0; i < wagons->length; i++) {
        wagon w = mcall(wagons, get, i);

        out.LenString(w->id);
        out.LenString(w->type);
    }
    pop_save_config();
}

private void load_trains() {
    for (int i = 0; i < wagons->length; i++) {
        free(mcall(wagons, get, i));
    }
    mcall0(wagons, clear);

    if (!file_exists(CONFIG_FILE)) return;

    config_reader in = push_load_config(CONFIG_FILE);
    int length = in.Int();
    for (int i = 0; i < length; i++) {
        string id = in.LenString();
        string type = in.LenString();

        mcall(wagons, add, new(wagon, id, type));
    }
    pop_load_config();
}

override
void init_trains() {
    wagons = new(wagon_array);
    wagons_filtered = new(wagon_array);

    trains = new(train_array);
    
    load_trains();
}

constructor(wagon,
    string id,
    string type
) {
    wagon obj = malloc(sizeoftype(wagon));
    obj->id = id;
    obj->type = type;
    return obj;
}

override
void add_wagon(string id, string type) {
    mcall(wagons, add, new(wagon, id, type));

    save_trains();
}

override
bool wagon_exists(string id) {
    for (int i = 0; i < wagons->length; i++) {
        if (strcmp(mcall(wagons, get, i)->id, id) == 0) {
            return true;
        }
    }
    return false;
}

override
void wagons_apply_filter() {
    mcall0(wagons_filtered, clear);

    for (int i = 0; i < wagons->length; i++) {
        wagon w = mcall(wagons, get, i);

        if (wagons_id_filter != NULL && strstr(w->id, wagons_id_filter) == NULL) continue;
        if (wagons_type_filter != NULL && strstr(w->type, wagons_type_filter) == NULL) continue;

        mcall(wagons_filtered, add, w);
    }
}

override
void wagons_reset_filter() {
    wagons_id_filter = NULL;
    wagons_type_filter = NULL;
}

constructor(coupled_wagon,
    wagon wagon
) {
    coupled_wagon obj = malloc(sizeoftype(coupled_wagon));
    obj->wagon = wagon;
    obj->next_wagon = NULL;
    return obj;
}

constructor(train,
    string id
) {
    train obj = malloc(sizeoftype(train));
    obj->id = id;
    obj->next_wagon = NULL;
    return obj;
}

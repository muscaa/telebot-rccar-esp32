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
train_array trains_filtered;
string trains_id_filter;

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
    out.Int(trains->length);
    for (int i = 0; i < trains->length; i++) {
        train t = mcall(trains, get, i);

        out.LenString(t->id);
        
        // save coupled wagons
    }
    pop_save_config();
}

private void load_trains() {
    for (int i = 0; i < wagons->length; i++) {
        free(mcall(wagons, get, i));
    }
    mcall0(wagons, clear);

    for (int i = 0; i < trains->length; i++) {
        free(mcall(trains, get, i));

        // free coupled wagons
    }
    mcall0(trains, clear);

    if (!file_exists(CONFIG_FILE)) return;

    config_reader in = push_load_config(CONFIG_FILE);
    int wagons_length = in.Int();
    for (int i = 0; i < wagons_length; i++) {
        string id = in.LenString();
        string type = in.LenString();

        mcall(wagons, add, new(wagon, id, type));
    }
    int trains_length = in.Int();
    for (int i = 0; i < trains_length; i++) {
        string id = in.LenString();
        train t = new(train, id);

        // load coupled wagons

        mcall(trains, add, t);
    }
    pop_load_config();
}

override
void init_trains() {
    wagons = new(wagon_array);
    wagons_filtered = new(wagon_array);

    trains = new(train_array);
    trains_filtered = new(train_array);
    
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

override
void add_train(string id) {
    mcall(trains, add, new(train, id));

    save_trains();
}

override
bool train_exists(string id) {
    for (int i = 0; i < trains->length; i++) {
        if (strcmp(mcall(trains, get, i)->id, id) == 0) {
            return true;
        }
    }
    return false;
}

override
void trains_apply_filter() {
    mcall0(trains_filtered, clear);

    for (int i = 0; i < trains->length; i++) {
        train t = mcall(trains, get, i);

        if (trains_id_filter != NULL && strstr(t->id, trains_id_filter) == NULL) continue;

        mcall(trains_filtered, add, t);
    }
}

override
void trains_reset_filter() {
    trains_id_filter = NULL;
}

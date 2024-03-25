#pragma once

#include "../../utils/utils.h"

void init_trains();

type(wagon,
    string id,
    string type
) {
    string id;
    string type;
};

arraydef(wagon);

extern wagon_array wagons;

void add_wagon(string id, string type);

bool wagon_exists(string id);

extern wagon_array wagons_filtered;
extern string wagons_id_filter;
extern string wagons_type_filter;

void wagons_apply_filter();

void wagons_reset_filter();

type(coupled_wagon,
    wagon wagon
) {
    wagon wagon;
    coupled_wagon next_wagon;
};

type(train,
    string id
) {
    string id;
    coupled_wagon next_wagon;
};

arraydef(train);

extern train_array trains;

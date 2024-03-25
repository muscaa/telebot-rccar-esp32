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

void remove_wagon(string id);

int find_wagon(string id);

bool wagon_exists(string id);

extern wagon_array wagons_filtered;
extern string wagons_id_filter;
extern string wagons_type_filter;

void wagons_apply_filter();

void wagons_reset_filter();

type(coupled_wagon,
    wagon wagon
);

type(train,
    string id
) {
    string id;
    coupled_wagon next_wagon;
};

arraydef(train);

extern train_array trains;

void add_train(string id);

void remove_train(string id);

int find_train(string id);

bool train_exists(string id);

extern train_array trains_filtered;
extern string trains_id_filter;

void trains_apply_filter();

void trains_reset_filter();

#define TYPE_WAGON 0
#define TYPE_TRAIN 1

type(coupled_wagon,
    wagon wagon
) {
    wagon wagon;
    union {
        train train;
        coupled_wagon wagon;
    } prev_wagon;
    int prev_type;
    coupled_wagon next_wagon;
};

void couple(train t, wagon w);

void decouple(coupled_wagon cw);

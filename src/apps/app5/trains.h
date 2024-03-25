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

#pragma once

#include "../../utils/utils.h"

void init_trains();

type(locomotive,
    string id
) {
    string id;
};

arraydef(locomotive);

extern locomotive_array locomotives;

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
    locomotive locomotive
) {
    locomotive locomotive;
    coupled_wagon next_wagon;
};

arraydef(train);

extern train_array trains;

#include "trains.h"
#include <stdlib.h>

impl_arraydef(wagon);
impl_arraydef(train);

wagon_array wagons;
train_array trains;

override
void init_trains() {
    wagons = new(wagon_array);
    trains = new(train_array);
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

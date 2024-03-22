#include "trains.h"
#include <stdlib.h>

impl_arraydef(locomotive);
impl_arraydef(wagon);
impl_arraydef(train);

locomotive_array locomotives;
wagon_array wagons;
train_array trains;

override
void init_trains() {
    locomotives = new(locomotive_array);
    wagons = new(wagon_array);
    trains = new(train_array);
}

constructor(locomotive,
    string id
) {
    locomotive obj = malloc(sizeoftype(locomotive));
    obj->id = id;
    return obj;
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
    locomotive locomotive
) {
    train obj = malloc(sizeoftype(train));
    obj->locomotive = locomotive;
    obj->next_wagon = NULL;
    return obj;
}

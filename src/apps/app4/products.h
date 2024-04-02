#pragma once

#include "../../utils/utils.h"

void init_products();

type(product,
    string name,
    string type,
    string location
) {
    string name;
    string type;
    string location;
};

arraydef(product);

extern product_array products;

void add_product(string name, string type, string location);

void remove_product(string name);

int find_product(string name);

bool product_exists(string name);

// filter vars

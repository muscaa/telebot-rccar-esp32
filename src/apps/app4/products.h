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

extern product_array products_filtered;
extern string products_name_filter;
extern string products_type_filter;
extern string products_location_filter;
extern string products_quantity_filter;

void products_apply_filter();

void products_reset_filter();

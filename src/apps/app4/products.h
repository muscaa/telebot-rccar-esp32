#pragma once

#include "../../utils/utils.h"

void init_products();

type(reservation,
    string id,
    string name,
    int quantity
) {
    string id;
    string name;
    int quantity;
};

arraydef(reservation);

type(product,
    string name,
    string type,
    string location,
    int quantity
) {
    string name;
    string type;
    string location;
    int quantity;
    reservation_array reservations;

    int method0(product, available_quantity);
};

arraydef(product);

extern product_array products;

void add_product(string name, string type, string location, int quantity);

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

reservation create_reservation(product p, string name, int quantity);

void cancel_reservation(product p, string id);

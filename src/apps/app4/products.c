#include "products.h"

#define CONFIG_FILE "app4/products.dat"
#define UID_LENGTH 4

impl_arraydef(reservation);
impl_arraydef(product);

product_array products;
product_array products_filtered;
string products_name_filter;
string products_type_filter;
string products_location_filter;
string products_quantity_filter;

private void save_products() {
    string parent = file_parent(CONFIG_FILE);
    if (parent != NULL) dir_create(parent);

    config_writer out = push_save_config(CONFIG_FILE);
    out.Int(products->length);
    for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);

        out.LenString(p->name);
        out.LenString(p->type);
        out.LenString(p->location);
        out.Int(p->quantity);

        out.Int(p->reservations->length);
        for (int j = 0; j < p->reservations->length; j++) {
            reservation r = mcall(p->reservations, get, j);

            out.Bytes(r->uid->data, UID_LENGTH);
            out.LenString(r->name);
            out.Int(r->quantity);
        }
    }
    pop_save_config();
}

private void load_products() {
    for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);
        for (int j = 0; j < p->reservations->length; j++) {
            reservation r = mcall(p->reservations, get, j);
            delete(r->uid);
            free(r);
        }
        free(p);
    }
    mcall0(products, clear);

    if (!file_exists(CONFIG_FILE)) return;

    config_reader in = push_load_config(CONFIG_FILE);
    int products_length = in.Int();
    for (int i = 0; i < products_length; i++) {
        string name = in.LenString();
        string type = in.LenString();
        string location = in.LenString();
        int quantity = in.Int();

        product p = new(product, name, type, location, quantity);

        int reservations_length = in.Int();
        for (int j = 0; j < reservations_length; j++) {
            HASH uid = new(HASH, UID_LENGTH, in.Bytes(UID_LENGTH));
            string name = in.LenString();
            int quantity = in.Int();

            mcall(p->reservations, add, new(reservation, uid, p, name, quantity));
        }

        mcall(products, add, p);
    }
    pop_load_config();
}

override
void init_products() {
    products = new(product_array);
    products_filtered = new(product_array);

    load_products();
}

constructor(reservation,
    HASH uid,
    product product,
    string name,
    int quantity
) {
    reservation obj = malloc(sizeoftype(reservation));
    obj->uid = uid;
    obj->product = product;
    obj->name = name;
    obj->quantity = quantity;
    return obj;
}

private int impl_method0(product, available_quantity) {
    int reserved = 0;
    for (int i = 0; i < obj->reservations->length; i++) {
        reservation r = mcall(obj->reservations, get, i);
        reserved += r->quantity;
    }
    return obj->quantity - reserved;
}

constructor(product,
    string name,
    string type,
    string location,
    int quantity
) {
    product obj = malloc(sizeoftype(product));
    obj->name = name;
    obj->type = type;
    obj->location = location;
    obj->quantity = quantity;
    obj->reservations = new(reservation_array);
    set_impl(product, obj, available_quantity);
    return obj;
}

override
void add_product(string name, string type, string location, int quantity) {
    if (product_exists(name)) return;

    mcall(products, add, new(product, name, type, location, quantity));

    save_products();
}

override
void remove_product(string name) {
    int index = find_product(name);
    if (index == -1) return;

    free(mcall(products, get, index));
    mcall(products, remove, index);

    save_products();
}

override
int find_product(string name) {
    for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);

        if (strcmp(p->name, name) == 0) return i;
    }
    return -1;
}

override
bool product_exists(string name) {
    return find_product(name) != -1;
}

override
void products_apply_filter() {
    mcall0(products_filtered, clear);

    for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);

        if (products_name_filter != NULL && strstr(lower(p->name), lower(products_name_filter)) == NULL) continue;
        if (products_type_filter != NULL && strstr(lower(p->type), lower(products_type_filter)) == NULL) continue;
        if (products_location_filter != NULL && strstr(lower(p->location), lower(products_location_filter)) == NULL) continue;
        if (products_quantity_filter != NULL && p->quantity != atoi(products_quantity_filter)) continue;

        mcall(products_filtered, add, p);
    }
}

override
void products_reset_filter() {
    products_name_filter = NULL;
    products_type_filter = NULL;
    products_location_filter = NULL;
    products_quantity_filter = NULL;
}

private bool reservation_exists(HASH uid) {
    for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);

        for (int j = 0; j < p->reservations->length; j++) {
            reservation r = mcall(p->reservations, get, j);

            if (mcall(uid, equals, r->uid)) return true;
        }
    }
    return false;
}

override
reservation create_reservation(product p, string name, int quantity) {
    if (quantity > mcall0(p, available_quantity)) return NULL;

    reservation r = new(reservation, new(HASH_random, UID_LENGTH, reservation_exists), p, name, quantity);
    mcall(p->reservations, add, r);

    save_products();

    return r;
}

override
void cancel_reservation(product p, HASH uid) {
    int index = -1;
    for (int i = 0; i < p->reservations->length; i++) {
        reservation r = mcall(p->reservations, get, i);

        if (mcall(uid, equals, r->uid)) {
            index = i;
            break;
        }
    }
    if (index == -1) return;

    free(mcall(p->reservations, get, index));
    mcall(p->reservations, remove, index);

    save_products();
}

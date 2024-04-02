#include "products.h"

#define CONFIG_FILE "app4/products.dat"

impl_arraydef(product);

product_array products;

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
    }
    pop_save_config();
}

private void load_products() {
    for (int i = 0; i < products->length; i++) {
        free(mcall(products, get, i));
    }
    mcall0(products, clear);

    if (!file_exists(CONFIG_FILE)) return;

    config_reader in = push_load_config(CONFIG_FILE);
    int products_length = in.Int();
    for (int i = 0; i < products_length; i++) {
        string name = in.LenString();
        string type = in.LenString();
        string location = in.LenString();

        mcall(products, add, new(product, name, type, location));
    }
    pop_load_config();
}

override
void init_products() {
    products = new(product_array);

    load_products();
}

override
void add_product(string name, string type, string location) {
    if (product_exists(name)) return;

    mcall(products, add, new(product, name, type, location));

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

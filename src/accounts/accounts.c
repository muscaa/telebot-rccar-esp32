#include "accounts.h"

#include "../screens/accounts_noadmin.h"
#include "../screens/accounts.h"

#define ACCOUNTS_PATH "accounts/"
#define ADMIN_ACCOUNT ACCOUNTS_PATH "admin.dat"

impl_arraydef(account_permission);

private account logged_in_account = NULL;

destructor(account) {
    delete(obj->permissions);
}

constructor(account,
    string display_name,
    account_permission_array permissions
) {
    account obj = malloc(sizeoftype(account));
    obj->display_name = display_name;
    obj->permissions = permissions;
    set_impl(account, obj, __destruct);
    return obj;
}

override
void init_accounts() {
    if (!file_exists(ADMIN_ACCOUNT)) {
        string parent = file_parent(ADMIN_ACCOUNT);
        dir_create(parent);

        screen_noadmin();
        return;
    }

    screen_accounts();
}

/*private UID hash_password(string password) {
    byte bytes[strlen(password)];
    string_to_bytes(password, bytes);

    byte output[SHA256_BLOCK_SIZE];

    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, bytes, strlen(password));
    sha256_final(&ctx, output);

    return new(UID, SHA256_BLOCK_SIZE, output);
}*/

override
bool accounts_register(string username, string password) {
    string path = format(ACCOUNTS_PATH "%s.dat", username);
    if (file_exists(path)) return false;

    account_permission_array permissions = new(account_permission_array);
    if (strcmp(username, "admin") == 0) {
        mcall(permissions, add, ACCOUNT_PERMISSION_ADMIN);
    }

    //UID hash = hash_password(password);

    config_writer out = push_save_config(path);
    //out.Bytes(hash->data, SHA256_BLOCK_SIZE);
    out.LenString(password);

    out.Int(permissions->length);
    for (int i = 0; i < permissions->length; i++) {
        account_permission perm = mcall(permissions, get, i);
        out.Int(perm);
    }

    out.LenString(username);
    pop_save_config();

    return true;
}

override
bool accounts_login(string username, string password) {
    if (logged_in_account != NULL && !accounts_logout()) return false;

    string path = format(ACCOUNTS_PATH "%s.dat", username);
    if (!file_exists(path)) return false;

    //UID hash = hash_password(password);

    config_reader in = push_load_config(path);

    /*UID stored_hash = new(UID, SHA256_BLOCK_SIZE, in.Bytes(SHA256_BLOCK_SIZE));
    if (!mcall(hash, equals, stored_hash)) {
        pop_load_config();

        delete(stored_hash);

        return false;
    }

    delete(stored_hash);*/

    string stored_password = in.LenString();
    if (strcmp(password, stored_password) != 0) {
        pop_load_config();
        return false;
    }

    account_permission_array permissions = new(account_permission_array);
    int permissions_length = in.Int();
    for (int i = 0; i < permissions_length; i++) {
        account_permission perm = in.Int();
        mcall(permissions, add, perm);
    }

    string display_name = in.LenString();

    logged_in_account = new(account, display_name, permissions);

    pop_load_config();

    return true;
}

override
bool accounts_logout() {
    if (logged_in_account == NULL) return false;

    delete(logged_in_account);
    logged_in_account = NULL;

    return true;
}

override
account get_account_copy() {
    string display_name_copy = copy(logged_in_account->display_name);
    account_permission_array permissions_copy = new(account_permission_array);
    for (int i = 0; i < logged_in_account->permissions->length; i++) {
        account_permission perm = mcall(logged_in_account->permissions, get, i);
        mcall(permissions_copy, add, perm);
    }
    return new(account, display_name_copy, permissions_copy);
}

override
bool has_perm(account_permission permission) {
    if (logged_in_account == NULL) return false;

    for (int i = 0; i < logged_in_account->permissions->length; i++) {
        account_permission perm = mcall(logged_in_account->permissions, get, i);
        if (perm == ACCOUNT_PERMISSION_ADMIN || perm == permission) return true;
    }

    return false;
}

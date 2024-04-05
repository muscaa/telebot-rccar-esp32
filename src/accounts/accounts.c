#include "accounts.h"

#include "../screens/accounts_noadmin.h"
#include "../screens/accounts.h"

#define ACCOUNTS_PATH "accounts/"
#define ACCOUNTS_ADMIN ACCOUNTS_PATH "8C6976E5B5410415BDE908BD4DEE15DFB167A9C873FC4BB8A81F6F2AB448A918.dat"

impl_arraydef(account_permission);

private account logged_in = NULL;
private readonly_account readonly = NULL;

destructor(account) {
    delete(obj->uid);
    delete(obj->permissions);
}

constructor(account,
    HASH uid,
    string display_name,
    account_permission_array permissions
) {
    account obj = malloc(sizeoftype(account));
    obj->uid = uid;
    obj->display_name = display_name;
    obj->permissions = permissions;
    set_impl(account, obj, __destruct);
    return obj;
}

private HASH impl_function(readonly_account, uid) {
    return logged_in->uid;
}

private string impl_function(readonly_account, display_name) {
    return copy(logged_in->display_name);
}

private int impl_function(readonly_account, permissions_length) {
    return logged_in->permissions->length;
}

private account_permission impl_function(readonly_account, get_permission, int index) {
    return mcall(logged_in->permissions, get, index);
}

constructor(readonly_account) {
    if (readonly != NULL) return readonly;

    readonly_account obj = malloc(sizeoftype(readonly_account));
    set_impl(readonly_account, obj, uid);
    set_impl(readonly_account, obj, display_name);
    set_impl(readonly_account, obj, permissions_length);
    set_impl(readonly_account, obj, get_permission);
    return obj;
}

override
void init_accounts() {
    readonly = new(readonly_account);

    if (!file_exists(ACCOUNTS_ADMIN)) {
        string parent = file_parent(ACCOUNTS_ADMIN);
        dir_create(parent);

        screen_noadmin();
        return;
    }

    screen_accounts();
}

override
bool accounts_register(string username, string password) {
    HASH uid = sha256_hash_string(username);

    string path = format(ACCOUNTS_PATH "%s.dat", mcall0(uid, to_string));
    if (file_exists(path)) return false;

    account_permission_array permissions = new(account_permission_array);
    if (strcmp(username, "admin") == 0) {
        mcall(permissions, add, ACCOUNT_PERMISSION_ADMIN);
    }

    config_writer out = push_save_config(path);

    HASH pass_hash = sha256_hash_string(password);
    out.Bytes(pass_hash->data, SHA256_BLOCK_SIZE);
    delete(pass_hash);

    out.LenString(username);

    out.Int(permissions->length);
    for (int i = 0; i < permissions->length; i++) {
        account_permission perm = mcall(permissions, get, i);
        out.Int(perm);
    }
    pop_save_config();

    return true;
}

override
bool accounts_login(string username, string password) {
    if (logged_in != NULL && !accounts_logout()) return false;

    HASH uid = sha256_hash_string(username);

    string path = format(ACCOUNTS_PATH "%s.dat", mcall0(uid, to_string));
    if (!file_exists(path)) return false;

    config_reader in = push_load_config(path);

    HASH pass_hash = sha256_hash_string(password);
    HASH stored_hash = new(HASH, SHA256_BLOCK_SIZE, in.Bytes(SHA256_BLOCK_SIZE));
    if (!mcall(pass_hash, equals, stored_hash)) {
        delete(pass_hash);
        delete(stored_hash);

        pop_load_config();
        return false;
    }
    delete(pass_hash);
    delete(stored_hash);

    string display_name = in.LenString();

    account_permission_array permissions = new(account_permission_array);
    int permissions_length = in.Int();
    for (int i = 0; i < permissions_length; i++) {
        account_permission perm = in.Int();
        mcall(permissions, add, perm);
    }

    logged_in = new(account, uid, display_name, permissions);

    pop_load_config();

    return true;
}

override
bool accounts_logout() {
    if (logged_in == NULL) return false;

    delete(logged_in);
    logged_in = NULL;

    return true;
}

override
readonly_account get_account() {
    return logged_in == NULL ? NULL : readonly;
}

override
bool has_perm(account_permission permission) {
    if (logged_in == NULL) return false;

    for (int i = 0; i < logged_in->permissions->length; i++) {
        account_permission perm = mcall(logged_in->permissions, get, i);
        if (perm == ACCOUNT_PERMISSION_ADMIN || perm == permission) return true;
    }

    return false;
}

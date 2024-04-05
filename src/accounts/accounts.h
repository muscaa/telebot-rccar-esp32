#pragma once

#include "../utils/utils.h"

void init_accounts();

typedef enum {
    ACCOUNT_PERMISSION_ADMIN,
    ACCOUNT_PERMISSION_ADD_CONTENT,
    ACCOUNT_PERMISSION_REMOVE_CONTENT,
} account_permission;

arraydef(account_permission);

type(account,
    HASH uid,
    string display_name,
    account_permission_array permissions
) {
    HASH uid;
    string display_name;
    account_permission_array permissions;

    destruct(account);
};

type(readonly_account) {
    HASH function(uid);
    string function(display_name);
    int function(permissions_length);
    account_permission function(get_permission, int index);
};

bool accounts_register(string username, string password);

bool accounts_login(string username, string password);

bool accounts_logout();

readonly_account get_account();

bool has_perm(account_permission permission);

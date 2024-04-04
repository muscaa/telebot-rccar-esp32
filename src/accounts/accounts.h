#pragma once

#include "../utils/utils.h"

void init_accounts();

typedef enum {
    ACCOUNT_PERMISSION_ADMIN
} account_permission;

arraydef(account_permission);

type(account,
    string display_name,
    account_permission_array permissions
) {
    string display_name;
    account_permission_array permissions;

    destruct(account);
};

bool accounts_register(string username, string password);

bool accounts_login(string username, string password);

bool accounts_logout();

account get_account_copy();

bool has_perm(account_permission permission);

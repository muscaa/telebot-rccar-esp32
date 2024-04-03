#pragma once

#include "../types/byte.h"
#include "../types/string.h"

type(UID,
    int length,
    byte* data
) {
    int length;
    byte* data;

    string method0(UID, to_string);
    bool method(UID, equals, UID uid);
    destruct(UID);
};

UID construct(UID_random, int length, bool function(exists, UID uid));

string hex_string(byte* buf, int len);

void hex_bytes(byte* buf, string hex);
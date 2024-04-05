#pragma once

#include "../types/byte.h"
#include "../types/string.h"

type(HASH,
    int length,
    byte* data
) {
    int length;
    byte* data;

    string method0(HASH, to_string);
    bool method(HASH, equals, HASH hash);
    destruct(HASH);
};

HASH construct(HASH_random, int length, bool function(exists, HASH hash));

string hex_string(byte* buf, int len);

void hex_bytes(byte* buf, string hex);
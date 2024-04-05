#include "hash.h"

#include <stdlib.h>
#include "../defines.h"
#include "../system/random.h"

#define HEX_STRING "0123456789ABCDEF"
#define HEX_BYTES(c) ((c >= '0' && c <= '9') ? c - '0' : ((c >= 'A' && c <= 'F') ? c - 'A' + 10 : c - 'a' + 10))

private string impl_method0(HASH, to_string) {
    return hex_string(obj->data, obj->length);
}

private bool impl_method(HASH, equals, HASH hash) {
    if (obj->length != hash->length) return false;

    for (int i = 0; i < obj->length; i++) {
        if (obj->data[i] != hash->data[i]) return false;
    }

    return true;
}

destructor(HASH) {
    free(obj->data);
}

constructor(HASH,
    int length,
    byte* data
) {
    HASH obj = malloc(sizeoftype(HASH));
    obj->length = length;
    obj->data = data;
    set_impl(HASH, obj, to_string);
    set_impl(HASH, obj, equals);
    set_impl(HASH, obj, __destruct);
    return obj;
}

HASH construct(HASH_random, int length, bool function(exists, HASH hash)) {
    HASH obj = new(HASH, length, malloc(length));
    random_bytes(obj->data, length);
    if (exists != NULL) {
        while (exists(obj)) {
            random_bytes(obj->data, length);
        }
    }
    return obj;
}

override
string hex_string(byte* buf, int len) {
    string result = malloc(len * 2 + 1);
    for (int i = 0; i < len; i++) {
        byte v = buf[i] & 0xFF;
        
        result[i * 2] = HEX_STRING[v >> 4];
        result[i * 2 + 1] = HEX_STRING[v & 0x0F];
    }
    result[len * 2] = '\0';
    return result;
}

override
void hex_bytes(byte* buf, string hex) {
    int len = strlen(hex);
    for (int i = 0; i < len / 2; i++) {
        char c1 = hex[i * 2];
        char c2 = hex[i * 2 + 1];

        buf[i] = (HEX_BYTES(c1) << 4) | HEX_BYTES(c2);
    }
}

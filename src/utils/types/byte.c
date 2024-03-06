#include "byte.h"

#include <limits.h>

bool is_big_endian() {
    int big_endian = 1;
    return *((byte*) &big_endian) == 1;
}

void write_bytes(byte* p, int size, void (*out)(byte)) {
    if (is_big_endian()) {
        for (int i = 0; i < size; i++) {
            out(p[i]);
        }
    } else {
        for (int i = size - 1; i >= 0; i--) {
            out(p[i]);
        }
    }
}

void read_bytes(byte* p, int size, byte (*in)()) {
    if (is_big_endian()) {
        for (int i = 0; i < size; i++) {
            p[i] = in();
        }
    } else {
        for (int i = size - 1; i >= 0; i--) {
            p[i] = in();
        }
    }
}

// to bytes
void bool_to_bytes(bool v, void (*out)(byte)) {
    out(v ? 1 : 0);
}

void byte_to_bytes(byte v, void (*out)(byte)) {
    out(v);
}

void char_to_bytes(char v, void (*out)(byte)) {
    out(v);
}

void int_to_bytes(int v, void (*out)(byte)) {
    write_bytes((byte*) &v, sizeof(int), out);
}

void long_to_bytes(long v, void (*out)(byte)) {
    write_bytes((byte*) &v, sizeof(long), out);
}

void float_to_bytes(float v, void (*out)(byte)) {
    write_bytes((byte*) &v, sizeof(float), out);
}

void double_to_bytes(double v, void (*out)(byte)) {
    write_bytes((byte*) &v, sizeof(double), out);
}

// from bytes
bool bytes_to_bool(byte (*in)()) {
    return in() == 0 ? false : true;
}

byte bytes_to_byte(byte (*in)()) {
    return in();
}

char bytes_to_char(byte (*in)()) {
    byte b = in();
    return b > CHAR_MAX ? (b % (CHAR_MAX + 1)) - (CHAR_MAX + 1) : b;
}

int bytes_to_int(byte (*in)()) {
    int v;
    read_bytes((byte*) &v, sizeof(int), in);
    return v;
}

long bytes_to_long(byte (*in)()) {
    long v;
    read_bytes((byte*) &v, sizeof(long), in);
    return v;
}

float bytes_to_float(byte (*in)()) {
    float v;
    read_bytes((byte*) &v, sizeof(float), in);
    return v;
}

double bytes_to_double(byte (*in)()) {
    double v;
    read_bytes((byte*) &v, sizeof(double), in);
    return v;
}
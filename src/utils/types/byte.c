#include "byte.h"

#include <limits.h>

impl_arraydef(bool);
impl_arraydef(byte);

private bool is_big_endian() {
    int big_endian = 1;
    return *((byte*) &big_endian) == 1;
}

private void write_bytes(byte* p, int size, void function(out, byte)) {
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

private void read_bytes(byte* p, int size, byte function(in)) {
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
override
void bool_to_bytes(bool v, void function(out, byte)) {
    out(v ? 1 : 0);
}

override
void byte_to_bytes(byte v, void function(out, byte)) {
    out(v);
}

override
void char_to_bytes(char v, void function(out, byte)) {
    out(v);
}

override
void int_to_bytes(int v, void function(out, byte)) {
    write_bytes((byte*) &v, sizeof(int), out);
}

override
void long_to_bytes(long v, void function(out, byte)) {
    write_bytes((byte*) &v, sizeof(long), out);
}

override
void float_to_bytes(float v, void function(out, byte)) {
    write_bytes((byte*) &v, sizeof(float), out);
}

override
void double_to_bytes(double v, void function(out, byte)) {
    write_bytes((byte*) &v, sizeof(double), out);
}

// from bytes
override
bool bytes_to_bool(byte function(in)) {
    return in() == 0 ? false : true;
}

override
byte bytes_to_byte(byte function(in)) {
    return in();
}

override
char bytes_to_char(byte function(in)) {
    byte b = in();
    return b > CHAR_MAX ? (b % (CHAR_MAX + 1)) - (CHAR_MAX + 1) : b;
}

override
int bytes_to_int(byte function(in)) {
    int v;
    read_bytes((byte*) &v, sizeof(int), in);
    return v;
}

override
long bytes_to_long(byte function(in)) {
    long v;
    read_bytes((byte*) &v, sizeof(long), in);
    return v;
}

override
float bytes_to_float(byte function(in)) {
    float v;
    read_bytes((byte*) &v, sizeof(float), in);
    return v;
}

override
double bytes_to_double(byte function(in)) {
    double v;
    read_bytes((byte*) &v, sizeof(double), in);
    return v;
}

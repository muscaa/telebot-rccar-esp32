#pragma once

#include <stdbool.h>
#include <limits.h>

#define byte _Byte

typedef unsigned char _Byte;

// to bytes (to big endian)
void bool_to_bytes(bool v, void (*out)(byte));

void byte_to_bytes(byte v, void (*out)(byte));

void char_to_bytes(char v, void (*out)(byte));

void int_to_bytes(int v, void (*out)(byte));

void long_to_bytes(long v, void (*out)(byte));

void float_to_bytes(float v, void (*out)(byte));

void double_to_bytes(double v, void (*out)(byte));

// from bytes (from big endian)
bool bytes_to_bool(byte (*in)());

byte bytes_to_byte(byte (*in)());

char bytes_to_char(byte (*in)());

int bytes_to_int(byte (*in)());

long bytes_to_long(byte (*in)());

float bytes_to_float(byte (*in)());

double bytes_to_double(byte (*in)());
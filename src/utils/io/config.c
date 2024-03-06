#include "config.h"

#include <stdio.h>

// PRIVATE
int config = 0;
FILE* configs[100];

void write(byte b) {
    fwrite(&b, sizeof(byte), 1, configs[config - 1]);
}

byte read() {
    byte p;
    fread(&p, sizeof(byte), 1, configs[config - 1]);
    return p;
}

// writing
void write_bool(bool v) {
    bool_to_bytes(v, write);
}

void write_byte(byte v) {
    byte_to_bytes(v, write);
}

void write_char(char v) {
    char_to_bytes(v, write);
}

void write_int(int v) {
    int_to_bytes(v, write);
}

void write_long(long v) {
    long_to_bytes(v, write);
}

void write_float(float v) {
    float_to_bytes(v, write);
}

void write_double(double v) {
    double_to_bytes(v, write);
}

void write_len_string(string v) {
    
}

void write_string(string v) {

}

// reading
bool read_bool() {
    return bytes_to_bool(read);
}

byte read_byte() {
    return bytes_to_byte(read);
}

char read_char() {
    return bytes_to_char(read);
}

int read_int() {
    return bytes_to_int(read);
}

long read_long() {
    return bytes_to_long(read);
}

float read_float() {
    return bytes_to_float(read);
}

double read_double() {
    return bytes_to_double(read);
}

string read_len_string() {
    return NULL;
}

string read_string(int len) {
    return NULL;
}

config_writer writer = { write_bool, write_byte, write_char, write_int, write_long, write_float, write_double, write_len_string, write_string };
config_reader reader = { read_bool, read_byte, read_char, read_int, read_long, read_float, read_double, read_len_string, read_string };

// PUBLIC
void push_config(int mode, string file) {
    configs[config++] = fopen(file, mode == CONFIG_SAVE ? "wb" : "rb");
}

void pop_config() {
    fclose(configs[--config]);
}

void save(void (*f)(config_writer)) {
    f(writer);
}

void load(void (*f)(config_reader)) {
    f(reader);
}
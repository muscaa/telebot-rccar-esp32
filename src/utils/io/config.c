#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PRIVATE
int save = 0;
FILE* save_history[100];

int load = 0;
FILE* load_history[100];

void write(byte b) {
    fwrite(&b, sizeof(byte), 1, save_history[save - 1]);
}

byte read() {
    byte p;
    fread(&p, sizeof(byte), 1, load_history[load - 1]);
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

void write_string(string v) {
    for (int i = 0; i < strlen(v); i++) {
        write_char(v[i]);
    }
}

void write_len_string(string v) {
    write_int(strlen(v));
    write_string(v);
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

string read_string(int len) {
    char* s = malloc(len);
    for (int i = 0; i < len; i++) {
        s[i] = read_char();
    }
    return s;
}

string read_len_string() {
    int len = read_int();
    return read_string(len);
}

config_writer writer = { write_bool, write_byte, write_char, write_int, write_long, write_float, write_double, write_string, write_len_string };
config_reader reader = { read_bool, read_byte, read_char, read_int, read_long, read_float, read_double, read_string, read_len_string };

// PUBLIC
config_writer push_save_config(string file) {
    save_history[save++] = fopen(file, "wb");
    return writer;
}

void pop_save_config() {
    fclose(save_history[--save]);
}

config_reader push_load_config(string file) {
    load_history[load++] = fopen(file, "rb");
    return reader;
}

void pop_load_config() {
    fclose(load_history[--load]);
}
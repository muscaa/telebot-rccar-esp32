#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

private int save = 0;
private FILE* save_history[100];

private int load = 0;
private FILE* load_history[100];

private void write(byte b) {
    fwrite(&b, sizeof(byte), 1, save_history[save - 1]);
}

private byte read() {
    byte p;
    fread(&p, sizeof(byte), 1, load_history[load - 1]);
    return p;
}

// writing
private void write_bool(bool v) {
    bool_to_bytes(v, write);
}

private void write_byte(byte v) {
    byte_to_bytes(v, write);
}

private void write_char(char v) {
    char_to_bytes(v, write);
}

private void write_int(int v) {
    int_to_bytes(v, write);
}

private void write_long(long v) {
    long_to_bytes(v, write);
}

private void write_float(float v) {
    float_to_bytes(v, write);
}

private void write_double(double v) {
    double_to_bytes(v, write);
}

private void write_string(string v) {
    for (int i = 0; i < strlen(v); i++) {
        write_char(v[i]);
    }
}

private void write_len_string(string v) {
    write_int(strlen(v));
    write_string(v);
}

private void write_string_array(string_array v) {
    write_int(v->length);
    for (int i = 0; i < v->length; i++) {
        write_len_string(v->values[i]);
    }
}

// reading
private bool read_bool() {
    return bytes_to_bool(read);
}

private byte read_byte() {
    return bytes_to_byte(read);
}

private char read_char() {
    return bytes_to_char(read);
}

private int read_int() {
    return bytes_to_int(read);
}

private long read_long() {
    return bytes_to_long(read);
}

private float read_float() {
    return bytes_to_float(read);
}

private double read_double() {
    return bytes_to_double(read);
}

private string read_string(int len) {
    char* s = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        s[i] = read_char();
    }
    s[len] = '\0';
    return s;
}

private string read_len_string() {
    int len = read_int();
    return read_string(len);
}

private string_array read_string_array() {
    string_array a = new(string_array);
    a->length = read_int();
    a->values = malloc((a->length + 1) * sizeof(string));
    for (int i = 0; i < a->length; i++) {
        a->values[i] = read_len_string();
    }
    a->values[a->length] = NULL;
    return a;
}

private config_writer writer = {
    write_bool,
    write_byte,
    write_char,
    write_int,
    write_long,
    write_float,
    write_double,
    write_string,
    write_len_string,
    write_string_array
};
private config_reader reader = {
    read_bool,
    read_byte,
    read_char,
    read_int,
    read_long,
    read_float,
    read_double,
    read_string,
    read_len_string,
    read_string_array
};

override
config_writer push_save_config(string file) {
    save_history[save++] = fopen(file, "wb");
    return writer;
}

override
void pop_save_config() {
    fclose(save_history[--save]);
}

override
config_reader push_load_config(string file) {
    load_history[load++] = fopen(file, "rb");
    return reader;
}

override
void pop_load_config() {
    fclose(load_history[--load]);
}

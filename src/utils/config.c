#include "config.h"

// PRIVATE
/*
for (int i = 0; i < sizeof(int); i++) {
    unsigned char byte = (number >> (i * 8)) & 0xFF;
    fwrite(&byte, sizeof(unsigned char), 1, file);
}

for (int i = 0; i < sizeof(int); i++) {
    unsigned char byte;
    fread(&byte, sizeof(unsigned char), 1, file);
    number |= byte << (i * 8);
}
*/

// writing
void write_bool(bool v);
void write_byte(byte v);
void write_char(char v);
void write_int(int v);
void write_long(long v);
void write_float(float v);
void write_double(double v);
void write_len_string(string v);
void write_string(string v);

// reading
bool read_bool();
byte read_byte();
char read_char();
int read_int();
long read_long();
float read_float();
double read_double();
string read_len_string();
string read_string(int len);

config_writer writer = { write_bool, write_byte, write_char, write_int, write_long, write_float, write_double, write_len_string, write_string };
config_reader reader = { read_bool, read_byte, read_char, read_int, read_long, read_float, read_double, read_len_string, read_string };

int config = 0;
FILE* configs[100];

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

}
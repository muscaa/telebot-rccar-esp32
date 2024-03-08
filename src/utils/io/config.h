#pragma once

#include "../types/byte.h"
#include "../types/string.h"

typedef struct {
    void (*Bool)(bool);
    void (*Byte)(byte);
    void (*Char)(char);
    void (*Int)(int);
    void (*Long)(long);
    void (*Float)(float);
    void (*Double)(double);
    void (*String)(string);
    void (*LenString)(string);
} config_writer;

typedef struct {
    bool (*Bool)();
    byte (*Byte)();
    char (*Char)();
    int (*Int)();
    long (*Long)();
    float (*Float)();
    double (*Double)();
    string (*String)(int);
    string (*LenString)();
} config_reader;

config_writer push_save_config(string file);

void pop_save_config();

config_reader push_load_config(string file);

void pop_load_config();
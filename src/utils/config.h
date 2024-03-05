#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "string.h"
#include "byte.h"

#define CONFIG_SAVE 0
#define CONFIG_LOAD 1

typedef struct {
    void (*Bool)(bool);
    void (*Byte)(byte);
    void (*Char)(char);
    void (*Int)(int);
    void (*Long)(long);
    void (*Float)(float);
    void (*Double)(double);
    void (*LenString)(string);
    void (*String)(string);
} config_writer;

typedef struct {
    bool (*Bool)();
    byte (*Byte)();
    char (*Char)();
    int (*Int)();
    long (*Long)();
    float (*Float)();
    double (*Double)();
    string (*LenString)();
    string (*String)(int);
} config_reader;

void push_config(int mode, string file);

void pop_config();

void save(void (*f)(config_writer));

void load(void (*f)(config_reader));
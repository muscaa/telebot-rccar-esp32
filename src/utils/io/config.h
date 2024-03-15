#pragma once

#include "../defines.h"
#include "../types/byte.h"
#include "../types/string.h"

typedef struct {
    void function(Bool, bool);
    void function(Byte, byte);
    void function(Char, char);
    void function(Int, int);
    void function(Long, long);
    void function(Float, float);
    void function(Double, double);
    void function(String, string);
    void function(LenString, string);
    void function(StringArray, string_array);
} config_writer;

typedef struct {
    bool function(Bool);
    byte function(Byte);
    char function(Char);
    int function(Int);
    long function(Long);
    float function(Float);
    double function(Double);
    string function(String, int);
    string function(LenString);
    string_array function(StringArray);
} config_reader;

config_writer push_save_config(string file);

void pop_save_config();

config_reader push_load_config(string file);

void pop_load_config();
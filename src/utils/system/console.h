#pragma once

#include "../defines.h"
#include "../array/array.h"
#include "../types/string.h"
#include "system.h"

#define K_UP -38
#define K_DOWN -40
#define K_LEFT -37
#define K_RIGHT -39
#define K_RETURN 10
#define K_ESCAPE 27
#define K_SPACE ' '
#define K_BACKSPACE 8
#define K_DELETE 127
#define K_END -35
#define K_HOME -36
#define K_PAGE_UP -33
#define K_PAGE_DOWN -34

type(screen) {
    string_array lines;
    int_array stack;
    void method0(screen, push);
    void method(screen, append, string line);
    void method0(screen, new_line);
    void method0(screen, pop);
    void method(screen, push_foreground, const int color_code);
    void method0(screen, pop_foreground);
    void method(screen, push_background, const int color_code);
    void method0(screen, pop_background);
    destruct(screen);
};

arraydef(screen);

type(screen_renderer) {
    screen_array screens;
    screen method0(screen_renderer, push);
    void method0(screen_renderer, pop);
    void method0(screen_renderer, render);
    destruct(screen_renderer);
};

extern screen_renderer render_stack;

void clear_screen();

void set_console_title(string title);

void pause_console();

void print(string s, ...);

void println(string s, ...);

void start_capture();

int read_capture();

void stop_capture();

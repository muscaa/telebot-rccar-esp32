#pragma once

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

void get_screen_size(int* width, int* height);

void clear_screen();

void set_console_title(string title);

void pause_console();

void print(string s, ...);

void println(string s, ...);

void start_capture();

int read_capture();

void stop_capture();

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "console.h"

#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7

void push_foreground(const int color_code);

void push_foreground_rgb(const int red, const int green, const int blue);

void pop_foreground();

void push_background(const int color_code);

void push_background_rgb(const int red, const int green, const int blue);

void pop_background();

void push_reset();

void pop_reset();
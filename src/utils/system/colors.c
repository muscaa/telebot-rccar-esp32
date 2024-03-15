#include "colors.h"

#include <stdio.h>
#include <stdlib.h>

#include "../defines.h"
#include "console.h"

private int len(int n) {
    if (n == 0) return 1;
    int len = 0;
    for (; n != 0; len++, n /= 10);
    return len;
}

private char* color(int base, int code) {
    int color = base + code;
    char* out = malloc(3 + len(color));
    sprintf(out, "\033[%dm", color);
    return out;
}

private char* true_color(int base, int red, int green, int blue) {
    char* out = malloc(8 + len(base) + len(red) + len(green) + len(blue));
    sprintf(out, "\033[%d;2;%d;%d;%dm", base, red, green, blue);
    return out;
}

private int foreground = 0;
private char* foreground_history[100];

private int background = 0;
private char* background_history[100];

private void push_foreground_color(char* color) {
    foreground_history[foreground++] = color;
    print("%s", color);
}

private void push_background_color(char* color) {
    background_history[background++] = color;
    print("%s", color);
}

private void pop_foreground_color() {
    if (--foreground <= 0) {
        print("%s", color(0, 0));
        return;
    }
    char* last = foreground_history[foreground];
    free(last);
    print("%s", foreground_history[foreground - 1]);
}

private void pop_background_color() {
    if (--background <= 0) {
        print("%s", color(0, 0));
        return;
    }
    char* last = background_history[background];
    free(last);
    print("%s", background_history[background - 1]);
}

override
void push_foreground(const int color_code) {
    push_foreground_color(color(30, color_code));
}

override
void push_foreground_rgb(const int red, const int green, const int blue) {
    push_foreground_color(true_color(38, red, green, blue));
}

override
void pop_foreground() {
    pop_foreground_color();
}

override
void push_background(const int color_code) {
    push_background_color(color(40, color_code));
}

override
void push_background_rgb(const int red, const int green, const int blue) {
    push_background_color(true_color(48, red, green, blue));
}

override
void pop_background() {
    pop_background_color();
}

override
void push_reset() {
    push_foreground_color(color(0, 0));
    push_background_color(color(0, 0));
}

override
void pop_reset() {
    pop_foreground_color();
    pop_background_color();
}
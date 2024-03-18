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

private string color(int base, int code) {
    int color = base + code;
    string out = malloc(3 + len(color));
    sprintf(out, "\033[%dm", color);
    return out;
}

private string true_color(int base, int red, int green, int blue) {
    string out = malloc(8 + len(base) + len(red) + len(green) + len(blue));
    sprintf(out, "\033[%d;2;%d;%d;%dm", base, red, green, blue);
    return out;
}

private int foreground = 0;
private string foreground_history[100];

private int background = 0;
private string background_history[100];

override
string push_foreground_noprint(const int color_code) {
    string c = color(30, color_code);
    foreground_history[foreground++] = c;
    return c;
}

override
void push_foreground(const int color_code) {
    print("%s", push_foreground_noprint(color_code));
}

override
void push_foreground_rgb(const int red, const int green, const int blue) {
    string c = true_color(38, red, green, blue);
    foreground_history[foreground++] = c;
    print(c);
}

override
string pop_foreground_noprint() {
    if (--foreground <= 0) {
        return color(0, 0);
    }
    string last = foreground_history[foreground];
    free(last);
    return foreground_history[foreground - 1];
}

override
void pop_foreground() {
    print(pop_foreground_noprint());
}

override
string push_background_noprint(const int color_code) {
    string c = color(40, color_code);
    background_history[background++] = c;
    return c;
}

override
void push_background(const int color_code) {
    print(push_background_noprint(color_code));
}

override
void push_background_rgb(const int red, const int green, const int blue) {
    string c = true_color(48, red, green, blue);
    background_history[background++] = c;
    print(c);
}

override
string pop_background_noprint() {
    if (--background <= 0) {
        return color(0, 0);
    }
    string last = background_history[background];
    free(last);
    return background_history[background - 1];
}

override
void pop_background() {
    print(pop_background_noprint());
}

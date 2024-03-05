#pragma once

#if defined(_WIN32)
    #define WIN 1
#elif defined(__unix__)
    #define UNIX 1
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "string.h"

#if WIN
    #include <Windows.h>

    /*#define K_UP VK_UP
    #define K_DOWN VK_DOWN
    #define K_LEFT VK_LEFT
    #define K_RIGHT VK_RIGHT
    #define K_RETURN 10
    #define K_ESCAPE VK_ESCAPE
    #define K_SPACE ' '
    #define K_BACKSPACE VK_BACK
    #define K_DELETE 127
    #define K_END VK_END
    #define K_POS1 VK_HOME
    #define K_PAGE_UP VK_PRIOR
    #define K_PAGE_DOWN VK_NEXT*/
#elif UNIX
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>

    /*#define K_UP -38
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
    #define K_PAGE_DOWN -34*/
#endif

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

void clear_screen();

void title(string title);

void pause_console();

void print(string s, ...);

void println(string s, ...);

void start_capture();

int read_capture();

void stop_capture();
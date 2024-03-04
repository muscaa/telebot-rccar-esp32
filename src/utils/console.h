#ifdef _WIN32
    #define WIN
#elif __unix__
    #define UNIX
#endif

#ifndef _UTILS_CONSOLE_H_
    #define _UTILS_CONSOLE_H_
    
    #include <stdlib.h>
    #include <stdio.h>

    #include "string.h"

    #ifdef WIN
        #include <Windows.h>

        #define KEY_UP VK_UP
        #define KEY_DOWN VK_DOWN
        #define KEY_LEFT VK_LEFT
        #define KEY_RIGHT VK_RIGHT
        #define KEY_RETURN VK_RETURN
        #define KEY_ESCAPE VK_ESCAPE
        #define KEY_SPACE VK_SPACE
        #define KEY_BACK VK_BACK
    #elif UNIX
        // unix stuff
    #endif
#endif

void clear_screen();

void title(string title);

void pause();

void start_capture();

int read_capture();

void stop_capture();
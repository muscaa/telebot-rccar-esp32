#include "console.h"

// PUBLIC
void clear_screen() {
    #ifdef WIN
        system("cls");
    #elif UNIX
        system("clear");
    #endif
}

void title(string title) {
    #ifdef WIN
        system(concat("title ", title));
    #elif UNIX
        printf("\033]0;%s\007", title);
    #endif
}

void pause() {
    getchar();
}

#ifdef WIN
HANDLE hInput;
INPUT_RECORD input_record;
DWORD events_read;

void start_capture() {
    hInput = GetStdHandle(STD_INPUT_HANDLE);
}

int read_capture() {
    if (ReadConsoleInput(hInput, &input_record, 1, &events_read)) {
        if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
            return input_record.Event.KeyEvent.wVirtualKeyCode;
        }
    }
    return 0;
}

void stop_capture() {

}
#elif UNIX
void start_capture() {

}

int read_capture() {

}

void stop_capture() {

}
#endif
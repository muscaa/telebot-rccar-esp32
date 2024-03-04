#include "console.h"

// PUBLIC
void clear_screen() {
    #if WIN
        system("cls");
    #elif UNIX
        system("clear");
    #endif
}

void title(string title) {
    #if WIN
        system(concat("title ", title));
    #elif UNIX
        printf("\033]0;%s\007", title);
    #endif
}

void pause_console() {
    //getchar();
    pause();
}

void print(string s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    va_end(args);
}

void println(string s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    printf("\n");
    va_end(args);
}

#if WIN
HANDLE hInput;
INPUT_RECORD input_record;
DWORD events_read;

void start_capture() {
    hInput = GetStdHandle(STD_INPUT_HANDLE);
}

int read_capture() {
    /*if (ReadConsoleInput(hInput, &input_record, 1, &events_read)) {
        if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
            return input_record.Event.KeyEvent.wVirtualKeyCode;
        }
    }
    return 0;*/
        KEY_EVENT_RECORD keyevent;
    INPUT_RECORD irec;
    DWORD events;
    while(true) {
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &irec, 1, &events);
        if(irec.EventType==KEY_EVENT&&((KEY_EVENT_RECORD&)irec.Event).bKeyDown) {
            keyevent = (KEY_EVENT_RECORD&)irec.Event;
            const int ca = (int)keyevent.uChar.AsciiChar;
            const int cv = (int)keyevent.wVirtualKeyCode;
            const int key = ca==0 ? -cv : ca+(ca>0?0:256);
            switch(key) {
                case  -16: continue; // disable Shift
                case  -17: continue; // disable Ctrl / AltGr
                case  -18: continue; // disable Alt / AltGr
                case -220: continue; // disable first detection of "^" key (not "^" symbol)
                case -221: continue; // disable first detection of "`" key (not "`" symbol)
                case -191: continue; // disable AltGr + "#"
                case  -52: continue; // disable AltGr + "4"
                case  -53: continue; // disable AltGr + "5"
                case  -54: continue; // disable AltGr + "6"
                case  -12: continue; // disable num block 5 with num lock deactivated
                case   13: return  10; // enter
                case  -46: return 127; // delete
                case  -49: return 251; // ¹
                case    0: continue;
                case    1: continue; // disable Ctrl + a (selects all text)
                case    2: continue; // disable Ctrl + b
                case    3: continue; // disable Ctrl + c (terminates program)
                case    4: continue; // disable Ctrl + d
                case    5: continue; // disable Ctrl + e
                case    6: continue; // disable Ctrl + f (opens search)
                case    7: continue; // disable Ctrl + g
                //case    8: continue; // disable Ctrl + h (ascii for backspace)
                //case    9: continue; // disable Ctrl + i (ascii for tab)
                case   10: continue; // disable Ctrl + j
                case   11: continue; // disable Ctrl + k
                case   12: continue; // disable Ctrl + l
                //case   13: continue; // disable Ctrl + m (breaks console, ascii for new line)
                case   14: continue; // disable Ctrl + n
                case   15: continue; // disable Ctrl + o
                case   16: continue; // disable Ctrl + p
                case   17: continue; // disable Ctrl + q
                case   18: continue; // disable Ctrl + r
                case   19: continue; // disable Ctrl + s
                case   20: continue; // disable Ctrl + t
                case   21: continue; // disable Ctrl + u
                case   22: continue; // disable Ctrl + v (inserts clipboard)
                case   23: continue; // disable Ctrl + w
                case   24: continue; // disable Ctrl + x
                case   25: continue; // disable Ctrl + y
                case   26: continue; // disable Ctrl + z
                default: return key; // any other ASCII/virtual character
            }
        }
    }
}

void stop_capture() {
}
#elif UNIX
struct termios term;

void start_capture() {
    tcgetattr(0, &term);

    term.c_lflag &= ~(ICANON | ECHO); // turn off line buffering and echoing
    tcsetattr(0, TCSANOW, &term);
}

// https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
int read_capture() {
    int nbbytes;
    ioctl(0, FIONREAD, &nbbytes); // 0 is STDIN
    if (!nbbytes) return 0; // no key pressed
    
    int key = (int) getchar();
    if (key == 27 || key == 194 || key == 195) { // escape, 194/195 is escape for °ß´äöüÄÖÜ
        key = (int) getchar();
        if (key == 91) { // [ following escape
            key = (int) getchar(); // get code of next char after \e[
            if (key == 49) { // F5-F8
                key = 62 + (int) getchar(); // 53, 55-57
                if (key == 115) key++; // F5 code is too low by 1
                getchar(); // take in following ~ (126), but discard code
            } else if (key == 50) { // insert or F9-F12
                key = (int) getchar();
                if (key == 126) { // insert
                    key = 45;
                } else { // F9-F12
                    key += 71; // 48, 49, 51, 52
                    if (key < 121) key++; // F11 and F12 are too low by 1
                    getchar(); // take in following ~ (126), but discard code
                }
            } else if (key == 51 || key == 53 || key == 54) { // delete, page up/down
                getchar(); // take in following ~ (126), but discard code
            }
        } else if (key == 79) { // F1-F4
            key = 32 + (int) getchar(); // 80-83
        }
        key = -key; // use negative numbers for escaped keys
    }

    if (key >= 0 && key <= 8) return 0;
    if (key >= 11 && key <= 26) return 0;
    
    switch (key) {
        case  127: return K_BACKSPACE;
        case  -27: return K_ESCAPE;
        case  -65: return K_UP;
        case  -66: return K_DOWN;
        case  -68: return K_LEFT;
        case  -67: return K_RIGHT;
        case  -51: return K_DELETE;
        case  -53: return K_PAGE_UP;
        case  -54: return K_PAGE_DOWN;
        case  -72: return K_POS1;
        case  -70: return K_END;
        /*case -164: return 132; // ä
        case -182: return 148; // ö
        case -188: return 129; // ü
        case -132: return 142; // Ä
        case -150: return 153; // Ö
        case -156: return 154; // Ü
        case -159: return 225; // ß
        case -181: return 230; // µ
        case -167: return 245; // §
        case -176: return 248; // °
        case -178: return 253; // ²
        case -179: return 252; // ³
        case -180: return 239; // ´*/
    }
    return key; // any other ASCII character
}

void stop_capture() {
    term.c_lflag |= (ICANON | ECHO); // turn on line buffering and echoing
    tcsetattr(0, TCSANOW, &term);
}
#endif
#include "files.h"

#include <stdio.h>

#if WIN
    #include <direct.h>
#elif UNIX
    #include <sys/stat.h>
#endif

bool file_exists(string path) {
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

bool create_file(string path) {
    FILE* file = fopen(path, "w");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

bool create_dirs(string path) {
    #if WIN
        return _mkdir(path) == 0;
    #elif UNIX
        return mkdir(path, 0777) == 0;
    #endif
}
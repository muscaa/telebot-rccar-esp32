#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../defines.h"

#if WIN
    #include <direct.h>
#elif UNIX
    #include <sys/stat.h>
#endif

override
bool file_exists(string path) {
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

override
bool file_create(string path) {
    FILE* file = fopen(path, "w");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

override
string file_parent(string path) {
    int i;
    for (i = strlen(path) - 1; i >= 0; i--) {
        if (path[i] == '/') break;
    }
    if (i == -1) return NULL;

    char* new_path = malloc(i + 1);
    memcpy(new_path, path, i);
    new_path[i] = '\0';

    return new_path;
}

override
bool dir_create(string path) {
    #if WIN
        return _mkdir(path) == 0;
    #elif UNIX
        return mkdir(path, 0777) == 0;
    #endif
}

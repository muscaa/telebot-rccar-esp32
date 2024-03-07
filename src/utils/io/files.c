#include "files.h"

#include <stdio.h>
#include <sys/stat.h>

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
    return mkdir(path, 0777) == 0;
}
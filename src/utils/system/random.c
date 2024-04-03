#include "random.h"

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../defines.h"

private bool inited = false;

private void init_random() {
    if (inited) return;
    inited = true;

    srand(time(NULL));
}

override
int random_int(int min, int max) {
    init_random();

    return (rand() % (max - min)) + min;
}

override
void random_bytes(byte* buf, int len) {
    init_random();

    for (int i = 0; i < len; i++) {
        buf[i] = rand() % 256;
    }
}

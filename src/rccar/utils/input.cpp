#include "rccar/utils/input.h"

namespace rccar::utils::input {

void Digital::update(float delta) {
    prevValue = value;
    value = func();
}

void Analog::update(float delta) {
    prevValue = value;
    value = func();
}

}

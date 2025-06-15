#pragma once

#include "rccar/utils/input.h"

namespace rccar::utils::controller {

extern input::Digital LEFT;
extern input::Digital UP;
extern input::Digital RIGHT;
extern input::Digital DOWN;

extern input::Digital UP_LEFT;
extern input::Digital UP_RIGHT;
extern input::Digital DOWN_RIGHT;
extern input::Digital DOWN_LEFT;

extern input::Digital SQUARE;
extern input::Digital TRIANGLE;
extern input::Digital CIRCLE;
extern input::Digital CROSS;

extern input::Digital SHARE;
extern input::Digital OPTIONS;
extern input::Digital PS_BUTTON;
extern input::Digital TOUCHPAD;

extern input::Digital L1;
extern input::Digital L2;
extern input::Digital L3;

extern input::Digital R1;
extern input::Digital R2;
extern input::Digital R3;

extern input::Analog L2_VALUE;
extern input::Analog R2_VALUE;

extern input::Analog L_STICK_X;
extern input::Analog L_STICK_Y;

extern input::Analog R_STICK_X;
extern input::Analog R_STICK_Y;

void update(float delta);

}

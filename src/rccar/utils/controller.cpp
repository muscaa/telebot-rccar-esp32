#include "rccar/utils/controller.h"

#include <ps5Controller.h>

namespace rccar::utils::controller {

input::Digital LEFT([]() { return ps5.Left(); });
input::Digital UP([]() { return ps5.Up(); });
input::Digital RIGHT([]() { return ps5.Right(); });
input::Digital DOWN([]() { return ps5.Down(); });

input::Digital UP_LEFT([]() { return ps5.UpLeft(); });
input::Digital UP_RIGHT([]() { return ps5.UpRight(); });
input::Digital DOWN_RIGHT([]() { return ps5.DownRight(); });
input::Digital DOWN_LEFT([]() { return ps5.DownLeft(); });

input::Digital SQUARE([]() { return ps5.Square(); });
input::Digital TRIANGLE([]() { return ps5.Triangle(); });
input::Digital CIRCLE([]() { return ps5.Circle(); });
input::Digital CROSS([]() { return ps5.Cross(); });

input::Digital SHARE([]() { return ps5.Share(); });
input::Digital OPTIONS([]() { return ps5.Options(); });
input::Digital PS_BUTTON([]() { return ps5.PSButton(); });
input::Digital TOUCHPAD([]() { return ps5.Touchpad(); });

input::Digital L1([]() { return ps5.L1(); });
input::Digital L2([]() { return ps5.L2(); });
input::Digital L3([]() { return ps5.L3(); });

input::Digital R1([]() { return ps5.R1(); });
input::Digital R2([]() { return ps5.R2(); });
input::Digital R3([]() { return ps5.R3(); });

input::Digital DIGITAL_VALUES[22] = {
    LEFT, UP, RIGHT, DOWN,
    UP_LEFT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT,
    SQUARE, TRIANGLE, CIRCLE, CROSS,
    SHARE, OPTIONS, PS_BUTTON, TOUCHPAD,
    L1, L2, L3,
    R1, R2, R3
};

input::Analog L2_VALUE([]() { return ps5.L2Value() / 255.0F; });
input::Analog R2_VALUE([]() { return ps5.R2Value() / 255.0F; });

input::Analog L_STICK_X([]() { return (ps5.LStickX() + (ps5.LStickX() < 0 ? 1 : 0)) / 127.0F; });
input::Analog L_STICK_Y([]() { return (ps5.LStickY() + (ps5.LStickY() < 0 ? 1 : 0)) / 127.0F; });

input::Analog R_STICK_X([]() { return (ps5.RStickX() + (ps5.RStickX() < 0 ? 1 : 0)) / 127.0F; });
input::Analog R_STICK_Y([]() { return (ps5.RStickY() + (ps5.RStickY() < 0 ? 1 : 0)) / 127.0F; });

input::Analog ANALOG_VALUES[6] = {
    L2_VALUE, R2_VALUE,
    L_STICK_X, L_STICK_Y,
    R_STICK_X, R_STICK_Y
};

}

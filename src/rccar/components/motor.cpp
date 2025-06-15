#include "rccar/components/motor.h"

#include <Arduino.h>

#include "rccar/constants.h"
#include "rccar/utils/controller.h"

namespace rccar::components::motor {


const int GEAR_MAX = 5;
const int GEAR_SPEEDS_NORMAL[GEAR_MAX] = {
    40,
    60,
    80,
    100,
    120
};
const int GEAR_SPEEDS_TURBO[GEAR_MAX] = {
    51,
    102,
    153,
    204,
    255
};

static int gear = 0;
static bool turbo = false;

void setup() {
    int PWM_FREQ = 20000;
    int PWM_RESOLUTION = 8;

    ledcSetup(constants::CHANNEL_MOTOR_R_PWM, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(constants::PIN_MOTOR_R_PWM, constants::CHANNEL_MOTOR_R_PWM);

    ledcSetup(constants::CHANNEL_MOTOR_L_PWM, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(constants::PIN_MOTOR_L_PWM, constants::CHANNEL_MOTOR_L_PWM);
}

void setSpeed(int speed) {
    speed = constrain(speed, -255, 255);

    if (speed > 0) {
        ledcWrite(constants::CHANNEL_MOTOR_L_PWM, 0);
        delay(10);
        ledcWrite(constants::CHANNEL_MOTOR_R_PWM, speed);
    } else if (speed < 0) {
        ledcWrite(constants::CHANNEL_MOTOR_R_PWM, 0);
        delay(10);
        ledcWrite(constants::CHANNEL_MOTOR_L_PWM, -speed);
    } else {
        ledcWrite(constants::CHANNEL_MOTOR_R_PWM, 0);
        ledcWrite(constants::CHANNEL_MOTOR_L_PWM, 0);
    }
}

void setSpeedGear(float value, bool reverse) {
    if (gear == 0) {
        gear = 1;
    }

    if (utils::controller::R1.isPressed()) {
        gear = constrain(gear + 1, 1, GEAR_MAX);
    } else if (utils::controller::L1.isPressed()) {
        gear = constrain(gear - 1, 1, GEAR_MAX);
    }

    setSpeed(static_cast<int>(value * (turbo ? GEAR_SPEEDS_TURBO : GEAR_SPEEDS_NORMAL)[gear - 1] * (reverse ? -1 : 1)));
}

void update(float delta) {
    if (utils::controller::TRIANGLE.isPressed()) {
        turbo = !turbo;
    }

    if (utils::controller::R2.isDown()) {
        setSpeedGear(utils::controller::R2_VALUE.getValue(), false);
    } else if (utils::controller::L2.isDown()) {
        setSpeedGear(utils::controller::L2_VALUE.getValue(), true);
    } else {
        gear = 0;
        setSpeed(0);
    }

    digitalWrite(2, turbo ? HIGH : LOW);
}

}

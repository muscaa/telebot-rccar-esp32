#include "rccar/components/servo.h"

#include <Arduino.h>
#include <ESP32Servo.h>

#include "rccar/constants.h"
#include "rccar/utils/controller.h"
#include "rccar/rccar.h"

namespace rccar::components::servo {

const float DEADZONE = 0.1F;

static Servo servo;

void setup() {
    servo.attach(constants::PIN_SERVO);
}

void update(float delta) {
    float stick = utils::controller::L_STICK_X.getValue();

    if (stick < DEADZONE && stick > -DEADZONE) {
        servo.write(90);
        return;
    }

    servo.write(static_cast<int>(90 + 90 * stick * 0.15F * (inverted_controls ? 1 : -1)));
}

}

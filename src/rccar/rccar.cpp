#include "rccar/rccar.h"

#include "rccar/utils/controller.h"
#include "rccar/components/servo.h"
#include "rccar/components/motor.h"

namespace rccar {

void setup() {
    components::servo::setup();
    components::motor::setup();
}

void init() {

}

void update(float delta) {
    for (utils::input::Digital& input : utils::controller::DIGITAL_VALUES) {
        input.update(delta);
    }
    for (utils::input::Analog& input : utils::controller::ANALOG_VALUES) {
        input.update(delta);
    }

    components::servo::update(delta);
    components::motor::update(delta);
}

void dispose() {
    
}

}

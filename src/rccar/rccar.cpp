#include "rccar/rccar.h"

#include "rccar/utils/controller.h"
#include "rccar/components/servo.h"
#include "rccar/components/motor.h"

namespace rccar {

bool inverted_controls = false;

void setup() {
    components::servo::setup();
    components::motor::setup();
}

void init() {

}

void update(float delta) {
    utils::controller::update(delta);

    if (utils::controller::SQUARE.isPressed()) {
        inverted_controls = !inverted_controls;
    }

    components::servo::update(delta);
    components::motor::update(delta);
}

void dispose() {
    
}

}

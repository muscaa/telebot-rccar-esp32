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
    utils::controller::update(delta);
    components::servo::update(delta);
    components::motor::update(delta);
}

void dispose() {
    
}

}

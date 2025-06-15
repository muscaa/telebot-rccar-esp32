#include <Arduino.h>
#include <ps5Controller.h>

#include "rccar/rccar.h"
#include "rccar/constants.h"

unsigned long lastUpdate = 0;

void setup() {
    Serial.begin(115200);
    ps5.begin(rccar::constants::CONTROLLER_MAC);
    
    pinMode(2, OUTPUT);

    rccar::setup();
}

void loop() {
    while (!ps5.isConnected()) {
        Serial.println("Waiting for PS5 controller to connect...");
        delay(500);
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
    }

    Serial.println("PS5 controller connected!");

    rccar::init();
    
    lastUpdate = millis();
    while (ps5.isConnected()) {
        float delta = (millis() - lastUpdate) / 1000.0;
        lastUpdate = millis();

        rccar::update(delta);
    }

    rccar::dispose();

    Serial.println("PS5 controller disconnected!");
}

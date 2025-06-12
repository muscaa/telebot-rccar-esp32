#include <Arduino.h>
#include <ps5Controller.h>

void setup() {
    Serial.begin(115200);
    ps5.begin("88:03:4C:22:F9:CC");
    
    pinMode(2, OUTPUT);
}

void loop() {
    while (!ps5.isConnected()) {
        Serial.println("Waiting for PS5 controller to connect...");
        delay(1000);
    }

    Serial.println("PS5 controller connected!");

    while (ps5.isConnected()) {
        if (ps5.Square()) {
            digitalWrite(2, HIGH);
        } else {
            digitalWrite(2, LOW);
        }
    }

    Serial.println("PS5 controller disconnected!");
}

#include <Arduino.h>
#include <esp_log.h>

extern "C" void app_main() {
    initArduino();

    pinMode(2, OUTPUT);

    ESP_LOGI("app_main", "Starting Blink Example");

    while (true) {
        digitalWrite(2, HIGH);
        delay(1000);
        digitalWrite(2, LOW);
        delay(1000);
    }
}
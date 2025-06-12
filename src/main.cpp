#include <Arduino.h>
#include <ps5Controller.h>
#include <ESP32Servo.h>

const int SERVO_PIN = 27;
const int R_PWM_PIN = 26;
const int L_PWM_PIN = 25;

const int pwmChannel_R = 1;
const int pwmChannel_L = 2;
const int pwmFreq = 20000;
const int pwmResolution = 8;

const int deadzone = 10;

unsigned long lastUpdate = 0;
Servo servo;
float motorSpeedFactor = 0.0;

void setMotor(int speed) {
    speed = constrain(speed, -255, 255);

    if (speed > 0) {
        ledcWrite(pwmChannel_L, 0);
        delay(10);
        ledcWrite(pwmChannel_R, speed);
    } else if (speed < 0) {
        ledcWrite(pwmChannel_R, 0);
        delay(10);
        ledcWrite(pwmChannel_L, -speed);
    } else {
        ledcWrite(pwmChannel_R, 0);
        ledcWrite(pwmChannel_L, 0);
    }
}

void setup() {
    Serial.begin(115200);
    ps5.begin("88:03:4C:22:F9:CC");
    
    pinMode(2, OUTPUT);

    servo.attach(SERVO_PIN);

    ledcSetup(pwmChannel_R, pwmFreq, pwmResolution);
    ledcAttachPin(R_PWM_PIN, pwmChannel_R);

    ledcSetup(pwmChannel_L, pwmFreq, pwmResolution);
    ledcAttachPin(L_PWM_PIN, pwmChannel_L);
}

void update(float delta) {
    if (ps5.Square()) {
        digitalWrite(2, HIGH);
    } else {
        digitalWrite(2, LOW);
    }

    if (ps5.LStickX() < -deadzone) {
        servo.write(0);
    } else if (ps5.LStickX() > deadzone) {
        servo.write(180);
    } else {
        servo.write(90);
    }

    if (ps5.Up()) {
        motorSpeedFactor += 0.1 * delta;
        motorSpeedFactor = constrain(motorSpeedFactor, 0.0, 1.0);
    } else if (ps5.Down()) {
        motorSpeedFactor -= 0.1 * delta;
        motorSpeedFactor = constrain(motorSpeedFactor, 0.0, 1.0);
    }

    Serial.println(motorSpeedFactor);

    if (ps5.R2Value() > 0) {
        setMotor(ps5.R2Value() * motorSpeedFactor);
    } else if (ps5.L2Value() > 0) {
        setMotor(-ps5.L2Value() * motorSpeedFactor);
    } else {
        setMotor(0);
    }
}

void loop() {
    while (!ps5.isConnected()) {
        Serial.println("Waiting for PS5 controller to connect...");
        delay(1000);
    }

    Serial.println("PS5 controller connected!");

    lastUpdate = millis();

    while (ps5.isConnected()) {
        float delta = (millis() - lastUpdate) / 1000.0;
        lastUpdate = millis();

        update(delta);
    }

    Serial.println("PS5 controller disconnected!");
}

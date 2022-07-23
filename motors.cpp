#include <Arduino.h>
#include "motors.h"



DCMotor::DCMotor(int pins[2]):local_pin_copy(pins) {
    // setting all pins als output
    for (int i = 0; i <= sizeof(local_pin_copy)/sizeof(local_pin_copy[0]); i++) {
        pinMode(local_pin_copy[i], OUTPUT);
    }
}

void DCMotor::runTime(bool direction, float duration) {
    // trun pins on
    runContinously(direction);
    // run given time
    delay(duration);
    // turn pins off
    stop();
};

void DCMotor::runContinously(bool direction) {
    // trun pins on
    if (direction) {
        digitalWrite(local_pin_copy[1], LOW);
        digitalWrite(local_pin_copy[0], HIGH);
    } else {
        digitalWrite(local_pin_copy[0], LOW);
        digitalWrite(local_pin_copy[1], HIGH);
    }
};

void DCMotor::stop() {
    // turn pins off
    for (int i = 0; i <= sizeof(local_pin_copy)/sizeof(local_pin_copy[0]); i++) {
        digitalWrite(local_pin_copy[i], LOW);
    }

};

#include <stdio.h>
#include <math.h>
#include <Arduino.h>

#include "motors.h"



DCMotor::DCMotor(int pins[2]):local_pin_copy(pins) {}

void DCMotor::run(bool direction, float duration) {
    // trun pins on
    // wait given time
    // turn pins off
};

void DCMotor::run_continously(bool direction) {
    // turn pins on
};

void DCMotor::stop() {
    // turn pins off
};

int main() {
    int motorpins[2] = {2, 3};
    DCMotor mot0(motorpins);
    return 0;
}

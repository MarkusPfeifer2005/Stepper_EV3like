#include <Arduino.h>
#include "motors.h"



DCMotor::DCMotor(int pins[2]):pins(pins) {
    // setting all pins als output
    for (int i = 0; i <= sizeof(pins)/sizeof(pins[0]); i++) {
        pinMode(pins[i], OUTPUT);
    }
}

void DCMotor::runTime(bool direction, int velocity, float duration) {
    // trun pins on
    runContinously(direction, velocity);
    // run given time
    delay(duration);
    // turn pins off
    stop();
};

void DCMotor::runContinously(bool direction, int velocity) {
    if (velocity < 0 || velocity > 255) {
        Serial.println("Velocity must be int between 0 and 255!");
        exit(0);
    }
    // trun pins on
    if (direction) {
        analogWrite(pins[1], 0);
        analogWrite(pins[0], velocity);
    } else {
        analogWrite(pins[0], 0);
        analogWrite(pins[1], velocity);
    }
};

void DCMotor::stop() {
    // turn pins off
    for (int i = 0; i <= sizeof(pins)/sizeof(pins[0]); i++) {
        digitalWrite(pins[i], LOW);
    }

};


StepperMotor::StepperMotor(unsigned int pins[4], bool reverse):pins(pins), reverse(reverse), steps(32), gear_ratio(64), pos(0), num_coils(4) {
    for (int i = 0; i < num_coils; i++) {
        pinMode(pins[i], OUTPUT);
    }
};

void StepperMotor::runContinously(bool direction, float velocity, bool halfstepping) {    

    // defining step size
    float stepsize;
    if (halfstepping) {
        stepsize = .5;
    }
    else {
        stepsize = 1;
    }
    if (direction) {
        stepsize *= -1;
    }

    float pos = 0;
    float new_pos;
    while (true) {
        new_pos = pos + stepsize;
        if (new_pos < 0) {
            new_pos = num_coils - abs(stepsize);
        }
        else if (new_pos > num_coils - abs(stepsize)) {
            new_pos = 0;
        }

        // setting pin values
        for (int coil = 0; coil < num_coils; coil++) {
            int cut = (int)new_pos;
            int rounded = round(new_pos);
            if (rounded > num_coils - 1) {
                rounded = 0;
            }

            if (coil == cut || coil == rounded) {
                digitalWrite(pins[coil], 0);
            }
            else {
                digitalWrite(pins[coil], 1);
            }
        }

        pos = new_pos;
        delay(3*velocity);
    }
};
/*
void StepperMotor::runSteps(int steps, bool direction, float velocity, bool hold, bool halfstepping) {
    // defining step size
    float stepsize;
    if (halfstepping) {
        stepsize = .5;
    }
    else {
        stepsize = 1;
    }
    if (direction) {
        stepsize *= -1;
    }


    for (int step_counter = 0; step_counter < steps; step_counter++) {  // step_counter is not direction specific

        float new_internal_pos = step_counter * steps % stepsize;

        // setting pin values
        for (int coil = 0; coil < num_coils; coil++) {
            int cut = (int)new_pos;
            int rounded = round(new_pos);
            if (rounded > num_coils - 1) {
                rounded = 0;
            }

            if (coil == cut || coil == rounded) {
                digitalWrite(pins[coil], 0);
            }
            else {
                digitalWrite(pins[coil], 1);
            }
        }

        pos = new_pos;
        delay(3*velocity);
    }

    if (!hold) {
        for (int coil = 0; coil < num_coils; coil++) {
            digitalWrite(pins[coil], 1);
        }
    }

};
*/
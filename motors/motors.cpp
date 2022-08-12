#include <Arduino.h>
#include "motors.h"
//#include <math.h>



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


StepperMotor::StepperMotor(unsigned int pins[4], bool reverse):pins(pins), reverse(reverse), teeth(16), gear_ratio(64), pos(0), coils(4) {
    for (int i = 0; i < coils; i++) {
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
            new_pos = coils - abs(stepsize);
        }
        else if (new_pos > coils - abs(stepsize)) {
            new_pos = 0;
        }

        // setting pin values
        for (int coil = 0; coil < coils; coil++) {
            int cut = (int)new_pos;
            int rounded = round(new_pos);
            if (rounded > coils - 1) {
                rounded = 0;
            }

            if (coil == cut || coil == rounded) {
                digitalWrite(pins[coil], 1);
            }
            else {
                digitalWrite(pins[coil], 0);
            }
        }

        pos = new_pos;
        delay(3*velocity);
    }
};

void StepperMotor::runSteps(float steps, bool direction, float velocity, bool hold) {

    for (float step = 0; step <= steps; step+=0.5/*really??*/) {  // steps must be replaced by an expression using pos
        float pos_coils = fmod(step, coils);
        if (pos_coils == (int)pos_coils) {
            for (int coil = 0; coil < coils; coil++) {  /*iterating through coils*/
                if (coil == pos_coils) {
                    analogWrite(pins[coil], 1*255/* times max PWM value*/);
                }
                else {
                    analogWrite(pins[coil], 0);
                }
            }
        }
        else {
            int backward = fmod(floor(pos_coils), coils);  // not shure how this behaves on nagative values; without mod it would be larger than coils
            int forward = fmod(ceil(pos_coils), coils);  // not shure how this behaves on nagative values; without mod it would be larger than coils
            for (int coil = 0; coil < coils; coil++) {  /*iterating through coils*/
                if (coil == backward) {
                    analogWrite(pins[coil], ((int) pos_coils+1-pos_coils)*255/* times max PWM value*/);
                }
                else if (coil == forward) {
                    analogWrite(pins[coil], (pos_coils - (int) pos_coils)*255/* times max PWM value*/);
                }
                else {
                    analogWrite(pins[coil], 0);
                }
            }
        }

        delay(3*velocity);

    }
    
    if (!hold) {
        for (int coil = 0; coil < coils; coil++) {
            digitalWrite(pins[coil], 0);
        }
    }
};

/*
.)  finite def of step (internal marked, externeal (*gearratio) via getter)
.)  possibility to regulate voltage to ensure continous rotation
.)  pos noted in rad (0 - 2*pi)
*/

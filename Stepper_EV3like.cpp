#include <Arduino.h>
#include <math.h>
#include "Stepper_EV3like.h"


StepperMotor::StepperMotor(unsigned int pins[4]):pins(pins), teeth(8), gear_ratio(64), pos(0), coils(4), max_pwm(255) {
    for (int i = 0; i < coils; i++) {
        pinMode(pins[i], OUTPUT);
    }
};

/*Power all coils to hold current position.*/
void StepperMotor::hold() {
    float pos_coils = fmod(pos, coils);
    if (pos_coils == (int)pos_coils) {
        for (int coil = 0; coil < coils; coil++) {  /*iterating through coils*/
            if (coil == pos_coils) {
                digitalWrite(pins[coil], 1*max_pwm);
            }
            else {
                digitalWrite(pins[coil], 0);
            }
        }
    }
    else {
        int backward = fmod(floor(pos_coils), coils);  // without mod it would be larger than coils
        int forward = fmod(ceil(pos_coils), coils);  // without mod it would be larger than coils
        for (int coil = 0; coil < coils; coil++) {  /*iterating through coils*/
            if (coil == backward) {
                digitalWrite(pins[coil], ((int) pos_coils+1-pos_coils)*max_pwm);
            }
            else if (coil == forward) {
                digitalWrite(pins[coil], (pos_coils - (int) pos_coils)*max_pwm);
            }
            else {
                digitalWrite(pins[coil], 0);
            }
        }
    }
};

/*Turn off all coils.*/
void StepperMotor::release() {
    for (int coil = 0; coil < coils; coil++) {
        digitalWrite(pins[coil], 0);
    }
};

// Only useful when running more than one thread.
void StepperMotor::runContinously(float stepsize, float velocity) {
    is_running = true;
    while (true) {
        if (is_running == false){
            return;  // break the loop and do not continue anything
        }
        setPos(pos+stepsize);
        this->hold();
        delay(3*velocity);
    }
    is_running = false;
};

void StepperMotor::runSteps(float steps, float stepsize, float velocity, bool hold) {
    if (steps < 0) {
        steps = abs(steps);
        stepsize *= -1;
    }
    is_running = true;
    for (float step = 0; step <= steps; step += abs(stepsize)) {
        if (is_running == false){
            return;  // break the loop and do not continue anything
        }
        setPos(pos+stepsize);
        this->hold();
        delay(3/velocity);
    }
    if (!hold) {
        release();
    }
    is_running = false;
};

void StepperMotor::setPos(float pos) {
    // see: https://stackoverflow.com/questions/7594508/modulo-operator-with-negative-values
    this->pos = fmod(coils*teeth*gear_ratio + fmod(pos, coils*teeth*gear_ratio), coils*teeth*gear_ratio);  // position can only be positive
}

void StepperMotor::setPosRad(double rad) {
    // Inaccuracies might occur based on the inaccuracy of PI.
    double factor = (coils*teeth*gear_ratio) / (2*PI);
    setPos(rad*factor);
};

double StepperMotor::getPosRad() {
    // Inaccuracies might occur based on the inaccuracy of PI.
    double factor = (2*PI) / (coils*teeth*gear_ratio);
    return pos * factor;
};

void StepperMotor::runAngleRad(float angle, float stepsize, float velocity, bool hold) {
    // Inaccuracies might occur based on the inaccuracy of PI.
    double factor = (coils*teeth*gear_ratio) / (2*PI);
    runSteps(angle*factor, stepsize, velocity, hold);
};

void StepperMotor::runPosRad(float angle, float stepsize, float velocity, bool hold) {
    // Inaccuracies might occur based on the inaccuracy of PI.
    // Works only on positive stepsize.
    angle = fmod(2*PI + fmod(angle, 2*PI), 2*PI);
    runAngleRad(angle-getPosRad(), stepsize, velocity, hold);
};

// Only useful when running more than one thread.
void StepperMotor::stop(bool hold) {
    is_running = false;
    if (hold) {
        this->hold();
    }
    else {
        release();
    }
};

void StepperMotor::setPosDeg(double deg) {
    double factor = (coils*teeth*gear_ratio) / 360;
    setPos(deg*factor);
};

double StepperMotor::getPosDeg() {
    double factor = 360 / (coils*teeth*gear_ratio);
    return pos * factor;
};

void StepperMotor::runAngleDeg(float angle, float stepsize, float velocity, bool hold) {
    double factor = (coils*teeth*gear_ratio) / 360;
    runSteps(angle*factor, stepsize, velocity, hold);
};

// Works only on positive stepsize.
void StepperMotor::runPosDeg(float angle, float stepsize, float velocity, bool hold) {
    angle = fmod(360 + fmod(angle, 360), 360);
    runAngleDeg(angle-getPosDeg(), stepsize, velocity, hold);
};

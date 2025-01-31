#include <Arduino.h>
#include <Stepper_EV3like.h>
#include <math.h>

unsigned int motorpins[4] = {10, 11, 12, 13};
StepperMotor motor(motorpins);

void setup() {
    Serial.begin(115200);

    motor.runAngleDeg(90, 1, 1, false);  // basic operation
    motor.runPosDeg(0, 1, 1, false);  // return to initial position
    motor.setPosDeg(90);  // reset the angle
    motor.runPosRad(0, 1, 1, false);  // return again
    motor.setPosDeg(-90);  // negative values are also supported
    motor.runPosRad(0, 1, 1, false);  // using radiants
    motor.runAngleRad(PI/2, 1, .1, false);  // run very slow
    
    Serial.println(motor.getPosDeg());  // send current position
}

void loop() {}

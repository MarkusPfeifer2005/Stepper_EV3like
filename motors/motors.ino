#include "motors.h"


unsigned int motorpins[4] = {7, 8, 12, 13};
//unsigned int motorpins[4] = {6, 9, 10, 11};
StepperMotor mot2(motorpins, false);
StepperMotor *pointer_to_mot2 = &mot2;


void setup() {
    Serial.begin(115200);

    pointer_to_mot2->runAngleDeg(90, 0.5, 2, false);
    pointer_to_mot2->runPosDeg(0, 0.5, 2, false);
    //mot2.setPosDeg(180);
    Serial.println(mot2.getPosDeg());
}

void loop() {}

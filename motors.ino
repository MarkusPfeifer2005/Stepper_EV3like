#include <Servo.h>
#include "motors.h"


Servo myservo;
unsigned int motorpins[4] = {10, 11, 12, 13};
StepperMotor mot2(motorpins, false);


void setup() {
    Serial.begin(115200);


    myservo.attach(9);
    myservo.write(0);

    delay(1000);
    mot2.runSteps(50, true, 1, false, true);

}

void loop() {}

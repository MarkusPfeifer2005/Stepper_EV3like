#include "motors.h"


void setup() {
    //Serial.begin(115200);

    int motorpins[2] = {2, 7};
    DCMotor mot1(motorpins);
    
    mot1.runTime(true, 3*1000);
    mot1.runTime(false, 3*1000);

    mot1.runContinously(true);
    delay(5000);
    mot1.stop();
}

// the loop function runs over and over again forever
void loop() {}

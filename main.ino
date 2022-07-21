#include "motors.h"


void setup() {
  Serial.begin(115200);

  int motorpins[2] = {1, 2};
  DCMotor mot1(motorpins);

  mot1.run(true, 5);
    
}


void loop() {}

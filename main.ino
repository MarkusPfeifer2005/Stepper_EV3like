#include <Stepper.h>


// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
#define STEPS 8*4  // change this to the number of steps on your motor
Stepper stepper(STEPS, 8, 9, 10, 11);

// the previous reading from the analog input
int previous = 0;

void setup() {
  Serial.begin(115200);
  stepper.setSpeed(100);
}

int pos = 0;

void loop() {
  int new_pos = analogRead(A0);
  Serial.println(new_pos);

  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(new_pos - pos);

  // remember the previous value of the sensor
  pos = new_pos;
  
}
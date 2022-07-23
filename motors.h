#include <Arduino.h>

#ifndef MOTORS_H
#define MOTORS_H


class DCMotor{
private:
    int *local_pin_copy;
public:
    // constructor
    DCMotor(int pins[2]);

    // methods
    void runTime(bool direction, float duration);
    void runContinously(bool direction);
    void stop();
};

class StepperMotor{
private:
    int coils;
    int teeth_per_layer;
    int teeth_layers;
    int gear_reduction;

    float pos;
    void run_steps();
public:
    void run_angle();
    void run_pos();
};


#endif

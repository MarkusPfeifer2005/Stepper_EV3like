#include <Arduino.h>

#ifndef MOTORS_H
#define MOTORS_H


class DCMotor{
private:
    int *pins;
public:
    // constructor
    DCMotor(int pins[2]);

    // methods
    void runTime(bool direction, int velocity, float duration);
    void runContinously(bool direction, int velocity);
    void stop();
};

class StepperMotor{
private:
    unsigned int num_coils;
    unsigned int *pins;
    unsigned int steps;
    float gear_ratio;
    bool reverse;  // currently not implemented
    float pos;  // given in steps; not implemented

    

public:
    void runSteps(int steps, bool direction, float velocity, bool hold, bool halfstepping);
    // constructors
    StepperMotor(unsigned int pins[4], bool reverse);

    // methods
    void runContinously(bool direction, float velocity, bool halfstepping);
    void runAngle(float angle, bool direction, float velocity, bool hold);
    void runPos();
    void runCon();
    void stop(bool hold);
};


#endif

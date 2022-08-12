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
    unsigned int coils;     // 4
    unsigned int *pins;     // pointer variable
    unsigned int teeth;     // 8 teeth per coil
    float gear_ratio;       // 64
    bool reverse;           // currently not implemented
    float pos;              // given in steps(an internal unit); relative to origin; requires getter & setter

public:
    // constructors
    StepperMotor(unsigned int pins[4], bool reverse);

    // methods
    void runSteps(float steps, bool direction, float velocity, bool hold);
    void runAngle(float angle, bool direction, float velocity, bool hold);
    void runPos();
    void runContinously(bool direction, float velocity, bool halfstepping);
    void stop(bool hold);
};


#endif

/*
Stepper motor library to control the 28BYJ-48 stepper motor.
This library is heavily inspired by the motor API for the LEGO EV3 robot:
https://pybricks.com/ev3-micropython/ev3devices.html
*/

#include <Arduino.h>

#ifndef STEPPER_EV3LIKE_H
#define STEPPER_EV3LIKE_H

class StepperMotor{
private:
                            // Values for 28BYJ-48 stepper motor:
    unsigned int coils;     // 4
    unsigned int *pins;
    unsigned int teeth;     // 8 teeth per coil
    unsigned int max_pwm;   // the maximum PWM signal, that is equivalent to digital 1
    /*The usage of pwm is an experimental feature. It causes no problems
    in regular operation but its desired increase in accuracy remains
    untested. The idea is to be able to achieve sub-step accuracy.*/
    float gear_ratio;       // 64
    float pos;              // given in steps(an internal unit); relative to origin; requires getter & setter; max: coils*teeth*gear_ratio
    bool is_running = false;

    void setPos(float pos);
    void runSteps(float steps, float stepsize, float velocity, bool hold);

public:
    StepperMotor(unsigned int pins[4]);

    void runAngleRad(float angle, float stepsize, float velocity, bool hold);
    void runPosRad(float angle, float stepsize, float velocity, bool hold);
    void runContinously(float stepsize, float velocity);
    void stop(bool hold);
    void hold();
    void release();
    void setPosRad(double rad);
    double getPosRad();
    void setPosDeg(double deg);
    double getPosDeg();
    void runAngleDeg(float angle, float stepsize, float velocity, bool hold);
    void runPosDeg(float angle, float stepsize, float velocity, bool hold);
};

#endif

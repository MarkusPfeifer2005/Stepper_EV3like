#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;


class DCMotor{
    private:
        bool direction;
        float speed;
        int pins[2];
    public:
        // constructors
        DCMotor(int pins[2], float speed):speed(speed) {
            pins = pins;
        }

        // getters
        float get_speed() {
            return speed;
        }
};


class StepperMotor{
private:
    int coils;
    int teeth_per_layer;
    int teeth_layers;
    int gear_reduction;

    float pos;
    void run_steps() {};
public:
    void run_angle() {};
    void run_pos() {};
};



int main() {
    int motorpins[2] = {2, 3};
    DCMotor mot0(motorpins, 5);
    cout << "speed is:\t" << mot0.get_speed();

    return 0;
}

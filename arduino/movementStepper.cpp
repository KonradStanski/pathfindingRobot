/*Wiring:

*/
#include<Arduino.h>
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

#define motorPin5  8     // IN1 on the ULN2003 driver 2
#define motorPin6  9     // IN2 on the ULN2003 driver 2
#define motorPin7  10    // IN3 on the ULN2003 driver 2
#define motorPin8  11    // IN4 on the ULN2003 driver 2


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// variables
int turnSteps = 2100; // number of steps for a 90 degree turn
int lineSteps = -6600; //number of steps to drive straight
int stepperSpeed = 1000; //speed of the stepper (steps per second)
int steps1 = 0; // keep track of the step count for motor 1
int steps2 = 0; // keep track of the step count for motor 2

boolean turn1 = true; //keep track if we are turning or going straight next
boolean turn2 = true; //keep track if we are turning or going straight next

void left();
void right();

/////////change this to be function definitions
void setup() {
    init();
    delay(300); //sime time to put the robot down after swithing it on

    stepper1.setMaxSpeed(2000.0);
    stepper1.move(1);  // I found this necessary
    stepper1.setSpeed(stepperSpeed);

    stepper2.setMaxSpeed(2000.0);
    stepper2.move(-1);  // I found this necessary
    stepper2.setSpeed(stepperSpeed);
}//--(end setup )---


void left(){
    setup();
    int target = turnSteps;
    stepper1.move(target);
    stepper1.setSpeed(stepperSpeed);
    stepper2.move(target);
    stepper2.setSpeed(stepperSpeed);
    steps1 = stepper1.distanceToGo();
    while(steps1){
        stepper1.runSpeedToPosition();
        stepper2.runSpeedToPosition();
        steps1 = stepper1.distanceToGo();
    }
    return;
}


void right(){
    setup();
    int target = -turnSteps;
    stepper1.move(target);
    stepper1.setSpeed(stepperSpeed);
    stepper2.move(target);
    stepper2.setSpeed(stepperSpeed);
    steps1 = stepper1.distanceToGo();
    while(steps1){
        stepper1.runSpeedToPosition();
        stepper2.runSpeedToPosition();
        steps1 = stepper1.distanceToGo();
    }
    return;
}


void forward(){
    setup();
    int target = lineSteps;
    stepper1.move(-target);
    stepper1.setSpeed(stepperSpeed);
    stepper2.move(target);
    stepper2.setSpeed(stepperSpeed);
    steps1 = stepper1.distanceToGo();
    while(steps1){
        stepper1.runSpeedToPosition();
        stepper2.runSpeedToPosition();
        steps1 = stepper1.distanceToGo();
    }
    return;
}

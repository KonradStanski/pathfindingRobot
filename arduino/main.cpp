/*---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 274, Fall  2018
#
#    Final Project
# ---------------------------------------------------*/

/*
Functions for movement:
void left();
void right();
void forward();

Functions for communication:
int ();

Wiring:

*/

#include <Arduino.h>
#include <AccelStepper.h>



// Motor pin definitions
#define HALFSTEP 8
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

#define motorPin5  8     // IN1 on the ULN2003 driver 2
#define motorPin6  9     // IN2 on the ULN2003 driver 2
#define motorPin7  10    // IN3 on the ULN2003 driver 2
#define motorPin8  11    // IN4 on the ULN2003 driver 2


//Define functions:
void left( void );
void right( void );
void forward( void );

int * receivePath( void );



// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// variables
//wheel is 8.47cm diameter/ circ = 26.6cm
//4096 steps in a full rotation/ 1539 steps for 10cm
//about 1645 steps for a 90deg turn
int turnSteps = 1645; // number of steps for a 90 degree turn
int lineSteps = -4000; //number of steps to drive straight
int stepperSpeed = 1000; //speed of the stepper (steps per second)
int steps1 = 0; // keep track of the step count for motor 1
int steps2 = 0; // keep track of the step count for motor 2

// reset motors after move
void resetMot( void ) {
    stepper1.setMaxSpeed(2000.0);
    stepper1.move(1);  // I found this necessary
    stepper1.setSpeed(stepperSpeed);

    stepper2.setMaxSpeed(2000.0);
    stepper2.move(-1);  // I found this necessary
    stepper2.setSpeed(stepperSpeed);
}


void left( void ){
    //resetMot();
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
    stepper1.stop();
    stepper2.stop();
    delay(50);
    return;
}


void right( void ){
    //resetMot();
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
    stepper1.stop();
    stepper2.stop();
    delay(50);
    return;
}


void forward( void ){
    //resetMot();
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
    stepper1.stop();
    stepper2.stop();
    delay(50);
    return;
}


int * receivePath( void ) {
    static int pathlen;
    int pathin;
    while (Serial3.available() == 0) { }// block until read in length
    // Read in path length
    pathlen = Serial3.read();
    Serial.print("length received: ");
    Serial.println(pathlen);

    // Read in path

    static int * path;
    path = (int*)malloc(pathlen+1 * sizeof(int));
    path[0] = pathlen;
    for (int i = 1; i <= pathlen; i++) {
        while (Serial3.available() == 0){ } // wait until available
        Serial.print(i);
        Serial.print(" path received: ");
        pathin = Serial3.read();
        Serial.print(char(pathin));
        path[i] = pathin;
        Serial.println(path[i]);
    }
    delay(500);
    return path;
}


void process(int length, int * direc){
    Serial3.println("entering processing");
    Serial3.flush();
    Serial3.print("length is: ");
    Serial3.flush();
    Serial3.println(length);
    Serial3.flush();


    //Start with a move south
    forward();

    // Start state machine
    int state[1]; // init state
    state[0] = direc[1]; // get first state

    Serial3.print("first state: ");
    Serial3.flush();
    Serial3.println(char(state[0]));
    Serial3.flush();

    int next[1]; // init next
    for(int i = 2; i <= length; i++){

        Serial3.print("i is: ");
        Serial3.flush();
        Serial3.print(i);
        Serial3.flush();

        next[0] = direc[i];

        Serial3.print(" next state: ");
        Serial3.flush();
        Serial3.print(char(next[0]));
        Serial3.flush();



        if((state[0] == 78 && next[0] == 78) || (state[0] == 83 && next[0] == 83) || (state[0] == 69 && next[0] == 69) || (state[0] == 87 && next[0] == 87)){
            Serial3.println(" enter forward");
            Serial3.flush();
            forward();
        }else if((state[0] == 78 && next[0] == 83) || (state[0] == 83 && next[0] == 78) || (state[0] == 69 && next[0] == 87) || (state[0] == 87 && next[0] == 69)){
            Serial3.println(" enter turn 180 forward");
            Serial3.flush();
            right();
            right();
            forward();
        }else if((state[0] == 78 && next[0] == 69) || (state[0] == 83 && next[0] == 87) || (state[0] == 69 && next[0] == 83) || (state[0] == 87 && next[0] == 78)){
            Serial3.println(" enter right + forward");
            Serial3.flush();
            right();
            forward();
        }else if((state[0] == 78 && next[0] == 87) || (state[0] == 83 && next[0] == 69) || (state[0] == 69 && next[0] == 78) || (state[0] == 87 && next[0] == 83)){
            Serial3.println(" enter left + forward");
            Serial3.flush();
            left();
            forward();
        }
        state[0] = next[0];
    }
}


void setup() {
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
}


int main() {
    setup();
    int *path;
    path = receivePath();
    int length = path[0];
    resetMot();
    process(length, path);
    return 0;
}

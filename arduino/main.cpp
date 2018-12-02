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


/*
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
*/

//Define functions:
void left( void );
void right( void );
void forward( void );

int * receivePath( void );


/*
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// variables
int turnSteps = 2100; // number of steps for a 90 degree turn
int lineSteps = -6600; //number of steps to drive straight
int stepperSpeed = 1000; //speed of the stepper (steps per second)
int steps1 = 0; // keep track of the step count for motor 1
int steps2 = 0; // keep track of the step count for motor 2

// reset motors after move
void resetMot( void ) {
    init();
    delay(300); //sime time to put the robot down after swithing it on

    stepper1.setMaxSpeed(2000.0);
    stepper1.move(1);  // I found this necessary
    stepper1.setSpeed(stepperSpeed);

    stepper2.setMaxSpeed(2000.0);
    stepper2.move(-1);  // I found this necessary
    stepper2.setSpeed(stepperSpeed);
}


void left( void ){
    resetMot();
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


void right( void ){
    resetMot();
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


void forward( void ){
    resetMot();
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
*/

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

/*
void process(int length, char * direc){
    char state = direc[0];
    char next;
    for(int i = 1; i<length; i++){
        next = direc[i];
        if((state == "N" && next == "N") || (state == "S" && next == "S") || (state == "E" && next == "E") || (state == "W" && next == "W")){
            forward();
        }else if((state == "N" && next == "S") || (state == "S" && next == "N") || (state == "E" && next = "W") || (state == "W" && next == "E")){
            right();
            right();
            forward();
        }else if((state == "N" && next == "E") || (state == "S" && next == "W") || (state == "E" && next = "S") || (state == "W" && next == "N")){
            right();
            forward();
        }else if((state == "N" && next == "W") || (state == "S" && next == "E") || (state == "E" && next = "N") || (state == "W" && next == "S")){
            left();
            forward();
        }
    }
}
*/

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
    Serial.println(length);
    //process(length, direc);
    //executeMaze(length, direc);
    return 0;
}

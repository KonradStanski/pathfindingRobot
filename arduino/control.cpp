/*---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 274, Fall  2018
#
#    Final Project
# ---------------------------------------------------*/

/*
Functions for movement:
void turnL();
void turnR();
void advance();

Functions for communication:

*/
/*Wiring:

*/
#include <Arduino.h>
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

// Bluetooth init
const int ledpin = 13;
char val;

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// variables
int turnSteps = 2100; // number of steps for a 90 degree turn
int lineSteps = -6600; //number of steps to drive straight
int stepperSpeed = 1000; //speed of the stepper (steps per second)
int steps1 = 0; // keep track of the step count for motor 1
int steps2 = 0; // keep track of the step count for motor 2

boolean turn1 = false; //keep track if we are turning or going straight next
boolean turn2 = false; //keep track if we are turning or going straight next

void setup() {
    init();
    //init bluetooth comms
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(ledpin,OUTPUT);
    //TEST OUTPUT LED
    digitalWrite(ledpin, HIGH);
    delay(300);
    digitalWrite(ledpin, LOW);
    delay(300); //sime time to put the robot down after swithing it on

    //init stepper
    stepper1.setMaxSpeed(2000.0);
    stepper1.move(1);  // I found this necessary
    stepper1.setSpeed(stepperSpeed);

    stepper2.setMaxSpeed(2000.0);
    stepper2.move(-1);  // I found this necessary
    stepper2.setSpeed(stepperSpeed);
}//--(end setup )---


int main() {
    setup();
    while (true){
        // Receive from device
        if(Serial3.available()) {
            //Serial.print("Received");
            val = Serial3.read();
            Serial.print(val);

            // INDICATOR
            digitalWrite(ledpin, HIGH);
            //delay(200);
            digitalWrite(ledpin,LOW);
        }
        // Transmit to device
        if(Serial.available()) {
            //Serial3.print("Received")
            val = Serial.read();
            Serial3.print(val);

            //INDICATOR
            digitalWrite(ledpin, HIGH);
            //delay(200);
            digitalWrite(ledpin,LOW);
        }

    }
    return 0;
}


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
#include <Arduino.h>
#include <Servo.h>
#include <VirtualWire.h>
#include"movement.h"

//Definitions
Servo servoL; // create servo object for left servo
Servo servoR; // create servo object for right servo


void setup( void ){
    // Initialize
    init();

    // Define Pins
    servoL.attach(9);
    servoR.attach(10);

    // Start Serials
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);
}



int main( void ){
    // Run setup
    setup();

    // Put looping code here
    while(true) {
        servoL.write(90); // 90 is off, 180 is full cw, 0 is fill ccw
        servoR.write(90);
    }
    return 0;
}

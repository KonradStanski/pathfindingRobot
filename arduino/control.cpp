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
//#include "movement.h"
//#include "comms.h"

//Definitions
Servo servoL; // create servo object for left servo
Servo servoR; // create servo object for right servo

//movement functions (only here for now, will later move to movement.h)
void turnL( void ) {
    servoL.write(120);
    servoR.write(60);
    delay(300);
    servoL.write(90);
    servoR.write(90);
}


void turnR( void ){
    servoL.write(60);
    servoR.write(120);
    delay(300);
    servoL.write(90);
    servoR.write(90);
}


void advance( void ) {
    servoL.write(180);
    servoR.write(180);
    delay(160);
    servoL.write(90);
    servoR.write(90);
}


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

        turnR();
        delay(500);
        turnL();
        delay(500);



        //servoL.write(95); // 90 is off, 180 is full cw, 0 is fill ccw

    }
    return 0;
}

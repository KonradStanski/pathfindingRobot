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
char readInstrut();
*/
/*Wiring:

*/

#include <Arduino.h>
#include <AccelStepper.h>
#include "comms.h"

void setup() {
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(ledpin,OUTPUT);


}


int main() {
    setup();
    while (true){

    }
    return 0;
}

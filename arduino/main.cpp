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
#include "movementStepper.h"

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


void setup() {
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(ledpin,OUTPUT);
}


int main() {
    setup();
    char direc[] = getArr__prototype();
    int length = sizeof(direc)/sizeof(direc[0])-1;
    process(length, direc);
    executeMaze(length, direc);
    return 0;
}

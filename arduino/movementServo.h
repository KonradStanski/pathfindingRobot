/*---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 274, Fall  2018
#
#    Final Project
# ---------------------------------------------------*/

//movement functions
void turnL(servoL, servoR) {
    servoL.write(180);
    servoR.write(0);
    delay(160);
}


void turnR(servoL, servoR){
    servoL.write(0);
    servoR.write(180);
    delay(160);
}


void advance(servoL, servoR) {
    servoL.write(180);
    servoR.write(180);
    delay(160);
}
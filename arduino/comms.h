/*Wiring:
gnd ble to gnd ard
gnd ble to 5v ard
wire rx ble to tx3 ard
wire tx ble to rx3 ard
led on pin 13

*/
#include<Arduino.h>
const int ledpin = 13;
char val;

void setup(){
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(ledpin,OUTPUT);
    //TEST OUTPUT LED
    digitalWrite(ledpin, HIGH);
    delay(300);
    digitalWrite(ledpin, LOW);}

int main() {
    setup();

    while (true){

        // Receive from phone
        if(Serial3.available()) {
            //Serial.print("Received");
            val = Serial3.read();
            Serial.print(val);

            // INDICATOR
            digitalWrite(ledpin, HIGH);
            //delay(200);
            digitalWrite(ledpin,LOW);
        }
        // Transmit to phone
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
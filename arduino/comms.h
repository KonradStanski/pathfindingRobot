/*Wiring:
gnd ble to gnd ard
gnd ble to 5v ard
wire rx ble to tx3 ard
wire tx ble to rx3 ard
led on pin 13

*/
#include<Arduino.h>
const int ledpin = 13;
int val = 1;
int i = 0;

void setup(){
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(ledpin,OUTPUT);
    //TEST OUTPUT LED
    digitalWrite(ledpin, HIGH);
    delay(300);
    digitalWrite(ledpin, LOW);
}

int main() {
    setup();

    while (true){

        // Receive from bluetooth and send to comp
        if(Serial3.available()) {
            Serial.print(" Received ");
            val = Serial3.read();
            Serial3.print("sucessfully received: ");
            Serial3.println(char(val));
            Serial.print("val is: ");
            Serial.print(char(val));
            Serial.print(" ");
            Serial.println(val);
            i++;

            // INDICATOR
            digitalWrite(ledpin, HIGH);
            delay(1);
            digitalWrite(ledpin,LOW);
        }
        // Transmit from comp to bluetooth
        if(Serial.available()) {
            Serial3.print("Received ");
            val = Serial.read();
            Serial3.print("val is: ");
            Serial3.println(val);

            //INDICATOR
            digitalWrite(ledpin, HIGH);
            delay(1);
            digitalWrite(ledpin,LOW);
        }

    }

    return 0;
}

#include <Arduino.h>

#define LED 16
#define INTERRUPTPIN 0

void TakePin();

int val=0;

void setup() {
Serial.begin(9600);
pinMode(LED,OUTPUT);
attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN),TakePin,FALLING); 
}

void loop() {
  val=digitalRead(0);
  if (val==1) {
   digitalWrite(LED, HIGH);
    Serial.println("ON");
    delay(500);
    digitalWrite(LED, LOW);
    Serial.println("OFF");
    delay(500);
  }
  else {digitalWrite(LED, HIGH); Serial.println("ON");}
}

void TakePin () {

Serial.println("BOOT");

}
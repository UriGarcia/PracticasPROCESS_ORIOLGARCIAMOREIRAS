#include <Arduino.h>

#define LED 16
unsigned long myTime;

void setup(){
Serial.begin(9600);
pinMode(LED,OUTPUT);

}

void loop(){

  Serial.println(myTime);
  myTime = millis();
  while(millis()<myTime+1000);
  // delay(1000);
  digitalWrite(LED,HIGH);
  Serial.println("ON");

  myTime = millis();
  while(millis()<myTime+666);
  // delay(666);
  digitalWrite(LED,HIGH);
  Serial.println("OFF");
  digitalWrite(LED,LOW);
  myTime = millis();
  while(millis()<myTime+666);
  // delay(666);

}

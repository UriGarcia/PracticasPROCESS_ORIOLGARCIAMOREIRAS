#include <Arduino.h>
#define LED 18
#define interruptPin 0
unsigned long myTime;


void Task1(void * parameter);
void anotherTask(void * parameter);

void setup(){
  Serial.begin(115200);
  /* we create a new task here */
  xTaskCreate(
  anotherTask, /* Task function. */
  "another Task", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL); /* Task handle to keep track of created task */
  xTaskCreate(
  Task1, /* Task function. */
  "Task 1", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL);
}

void loop(){
  Serial.println("this is ESP32 Task");
  delay(1000);
}

void anotherTask( void * parameter ){
  /* loop forever */
  for(;;){
    Serial.println("this is another Task");
    delay(1000);
  }
  vTaskDelete( NULL );
}

void Task1(void * parameter){
  pinMode(LED,OUTPUT);
  for(;;){
    Serial.println(myTime); 
    delay(666);    
    digitalWrite(LED,HIGH);
    Serial.println("ON");
    delay(666);
    digitalWrite(LED,HIGH);
    Serial.println("OFF");
    digitalWrite(LED,LOW);
    delay(666);
  }
}
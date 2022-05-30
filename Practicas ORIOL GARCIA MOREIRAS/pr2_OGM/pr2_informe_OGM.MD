### Oriol Garcia Moreiras
###                                    </p>
    Processadors Digitals

</p>

# </br> PRÁCTICA 2  :  interrupción por GPIO  y interrupción por timer </p>

## Materiales interrupción por GPIO
 Placa ESP32 con el respectivo cable para conectar al pc,
 Resistencia (en mi caso 100k),
 LED,
 Cables y
 Protoboard.

 ## Materiales interrupción por timer
 Placa ESP32 con el respectivo cable para conectar al pc
Protoboard (extra para tener la placa quieta)


## </br> 2.1 Código interrupción por GPIO
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

## 2.2 Código interrupción por timer

#include <Arduino.h>

volatile int interruptCounter;
int totalInterruptCounter;
 
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
 
void setup() {
 
  Serial.begin(115200);
 
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
 
}
 
void loop() {
 
  if (interruptCounter > 0) {
 
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
 
    Serial.print("An interrupt as occurred. Total number: ");
    Serial.println(totalInterruptCounter);
 
  }
}

## </br> Explicación interrupción por GPIO
En esta práctica veremos lo mismo que en la práctica 1, pero con un extra. El extra del que hablo es "attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN),TakePin,FALLING); " y la acción "void TakePin () {Serial.println("BOOT")}", básicamente lo que hace el código es que una vez presionemos el botón "BOOT" nos saldrá por pantalla un indicador de que lo hemos presionado, pero lo importante es que el programa seguirá en marcha, es decir en bucle. Por lo tanto, nuestro LED se irá apagando y encendiendo cada medio segundo (0.5 s) y si presionamos BOOT nos saldrá por pantalla.

Imagen del programa en ejecución (salida por el puerto serie):


![](GPIO.png)


## </br> Explicación interrupción por timer
En esta práctica veremos como funciona un timer y que podemos hacer con este tipo de temporizadores. Su función es que al terminar un determinado numero de cuentas produce una interrupción, en nuestro caso el contador contará hacia arriba y por cada vez que incremente nos saldrá por pantalla el siguiente mensaje "An interrupt as occurred. Total number: ".

Imagen del programa en ejecución (salida por el puerto serie):

![](TIMER.png)

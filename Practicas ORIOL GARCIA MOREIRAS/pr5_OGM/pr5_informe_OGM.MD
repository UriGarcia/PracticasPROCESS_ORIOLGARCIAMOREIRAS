### Oriol Garcia Moreiras
###                                    </p>
    Processadors Digitals

</p>

# </br> PRÁCTICA 5 : Buses de comunicación I (introducción y I2c)

## Materiales

Placa ESP32 (nuestra placa),
Cables (Para conectar el led, la resistencia y la placa),
Protoboard (será nuestro lugar de trabajo),
Cable para conectar la placa al ordenador (PC),
Sensor de temperatura y humedad y
Display

## </br> 5.1 Escáner I2C
#include <Arduino.h>
#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(115200);
  while (!Serial); // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
void loop(){
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ){
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");
      nDevices++;
    }
    else if (error==4){
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  delay(5000); // wait 5 seconds for next scan
}



## </br> 5.2 Parte 2
#include <Arduino.h>
#include "SSD1306Wire.h"   
#include "ClosedCube_SHT31D.h"
#include "images.h"
#include <Wire.h>


void init_temp_hum_task(void);

SSD1306Wire display(0x3c, SDA, SCL);  
ClosedCube_SHT31D sht3xd;

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

void setup()
{
	Wire.begin();

  // Initialising the UI will init the display too.

	Serial.begin(115200);
	Serial.println("ClosedCube SHT3X-D Periodic Mode Example");
	Serial.println("supports SHT30-D, SHT31-D and SHT35-D");

	sht3xd.begin(0x44); // I2C address: 0x44 or 0x45

	Serial.print("Serial #");
	Serial.println(sht3xd.readSerialNumber());

	if (sht3xd.periodicStart(SHT3XD_REPEATABILITY_HIGH, SHT3XD_FREQUENCY_10HZ) != SHT3XD_NO_ERROR)
		Serial.println("[ERROR] Cannot start periodic mode");

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void loop()
{
	SHT31D result = sht3xd.periodicFetchData();
  // draw the current demo method
  float humd = result.rh;
  float temp = result.t;

  Serial.print("Time:");
  Serial.print(millis());
  Serial.print(" Temperature:");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humd, 1);
  Serial.print("%");

  Serial.println();


  // clear the display
  display.clear();
  // draw the current demo method
  //demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(128/2, 0, "HUMEDAD");
  display.setFont(ArialMT_Plain_16);
  display.drawString(128/2, 11, String(humd)+ "%");
  display.setFont(ArialMT_Plain_10);
  display.drawString(128/2, 30, "TEMPERATURA");
  display.setFont(ArialMT_Plain_16);
  display.drawString(128/2, 41, String(temp)+ "ºC");

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 54, String(millis()/3600000)+String(":")\
          +String((millis()/60000)%60)+String(":")\
          +String((millis()/1000)%(60)));

  // write the buffer to the display
  display.display();

  
  delay(100);

}

void printResult(String text, SHT31D result) {
	if (result.error == SHT3XD_NO_ERROR) {
		Serial.print(text);
		Serial.print(": T=");
		Serial.print(result.t);
		Serial.print("C, RH=");
		Serial.print(result.rh);
		Serial.println("%");
	} else {
		Serial.print(text);
		Serial.print(": [ERROR] Code #");
		Serial.println(result.error);
	}

}


## </br> Escáner I2C (TEMPERATURA Y HUMEDAD)
En esta práctica veremos como saber la humedad y temperatura que capta nuestro sensor en cada momento. Para ello, tendremos que conectar entre sí la placa, el sensor y el display para posteriormente ver por pantalla estos datos.

</br> Pines de nuestra placa:

![](pinesESP32.png)


El circuito de la práctica es el siguiente:
![](circuito.png)


La salida del puerto seria básicamente es una impresión de la temperatura y humedad cada 5 segundos (delay(5000)).






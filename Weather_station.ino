#include <Wire.h>
#include <Adafruit_BMP085.h>  //import this library
#include <Arduino.h>
#include "DHT.h"    //import this library
#define DHTPIN 8 
#define DHTTYPE DHT11  
Adafruit_BMP085 bmp;    //import this library
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library
char temperature[] = "Temp = 00.0 C  ";
char humidity[]  = "RH   = 00.0 %  ";
void setup()
{
 Serial.begin (9600);
  pinMode (2,INPUT);
  pinMode (8,OUTPUT);
  dht.begin();
}
void loop()
{
  Serial.println("1: Rain\n2: Temperature and Humidity\n3: Pressure and Altitude\nEnter your choice\n");
  if(Serial.available()>0)
  {
    int op = Serial.read();
    switch(op)
    {
      case 1:
      delay(1000);
      int sensorReading = analogRead(A0);
  if (sensorReading > 700)
  {
  Serial.println("Rain is Detected");
  }
 else
 {
  Serial.println("Rain is not Detected");
 }
Serial.println("--------------------------------------");
      break;
      case 2:
      delay(500);           // wait 1s between readings
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(RH) || isnan(Temp)) {
    Serial.println(F("Error reading temperature!"));
  Serial.println(F("Error reading humidity!"));
    return;
  }
 
  temperature[7]     = Temp / 10 + 48;
  temperature[8]     = Temp % 10 + 48;
  temperature[11]    = 223;
  humidity[7]        = RH / 10 + 48;
  humidity[8]        = RH % 10 + 48;
  Serial.print(F("Temperature: "));
    Serial.print(Temp);
    Serial.println(F("°C"));
    Serial.println("--------------------------------------");
    Serial.print(F("Humidity: "));
    Serial.print(RH);
    Serial.println(F("%"));
    Serial.println("--------------------------------------");
    break;
    case 3:
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.println("--------------------------------------");
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");
Serial.println("--------------------------------------");
    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");
Serial.println("--------------------------------------");
  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    Serial.println("--------------------------------------");
    Serial.println();
    delay(500);
    break;
    default:
    Serial.println("Invalid Option!!!\nChoose again");
    }
  }
}

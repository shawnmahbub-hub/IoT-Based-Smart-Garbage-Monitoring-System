#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

//give authentication code here
char auth[]="b358ca12ae3843c3a95cf0215de1f5ba";

//give the wifi ssid and password
char ssid[]="AndroidAP";
char pass[]="ecau2950";

// DHT Sensor
const int DHTPin = 5;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);
SimpleTimer timer;

//part for sending sensor value to the blynk application
void sendSensor()
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  //checking if the sensor is faled to send the value
  if(isnan(h)|| isnan(t))
  {
    Serial.println("Failed to read from DHT sensor");
    return;  
  }
  
  //sending the value of the sensor from dht11
  Blynk.virtualWrite(V5,h);
  Blynk.virtualWrite(V6,t);
}

void setup(void)
{ 
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  dht.begin();

  //setup a function to be called every second
  timer.setInterval(100L,sendSensor);

  //printing value for serial monitor
  Serial.println("Humidity and temperature \n\n");
  Serial.println("==========================================");
  delay(1000);

}

void loop() 
{
//    float h = dht.readHumidity();
//    float t = dht.readTemperature();

    //blynk
    Blynk.run();//initiates blynk
    timer.run();//initiates blynk

    
    //printing value for serial monitor
//    Serial.print("Current humidity = ");
//    Serial.print(h);
//    Serial.print("%  ");
//    Serial.print("temperature = ");
//    Serial.print(t); 
//    Serial.println("C  ");
//    delay(1000);
}

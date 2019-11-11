#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

//give authentication code here
char auth[]="ba4dce62000e4554a9f95d69abb65bb8";

//give the wifi ssid and password
char ssid[]="TOTOLINK_N200RE";
char pass[]="Roya10661220172";

//defining gpio pin for ultrasonic sensor
#define TRIGGER 2 //D4 in nodeMCU
#define ECHO    0 //D3 in nodeMCU

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
  Blynk.virtualWrite(V6,h);
  Blynk.virtualWrite(V7,t);
}

void setup(void)
{ 
  Serial.begin(9600); //serial monitor baud rate
  Blynk.begin(auth,ssid,pass); //calling blynk method with parameter
  
  dht.begin(); //initiates to take the value from environment

  //setting pin modes for ultrasonic sensor
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  //setup a function to be called every second
  timer.setInterval(100L,sendSensor);

  //printing value for serial monitor
  Serial.println("Humidity and temperature \n\n");
  Serial.println("==========================================");
  delay(1000);

}

void loop() 
{
    //dht11 part
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    //ultrasonic part
    long duration, distance;
    digitalWrite(TRIGGER, LOW);  
    delayMicroseconds(2); 
      
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10); 
      
    digitalWrite(TRIGGER, LOW);
    duration = pulseIn(ECHO, HIGH);
    distance = (duration/2) / 29.1;
    
    if (distance <= 300 && distance >=201){
       Blynk.virtualWrite(V3, 255);
       Blynk.email("sawon78656@gmail.com","Garbage Alert!!!","Box 1!Emergency!You must need to collect the garbage.");
    }
    
    else{
        Blynk.virtualWrite(V3, 0);
    }
    
    if (distance <= 200 && distance >=151){
        Blynk.virtualWrite(V2, 255);
        Blynk.email("sawon78656@gmail.com","Garbage Alert!!!","Box 1! It is high time to collect the garbage.");
        
    }
    
    else {
        Blynk.virtualWrite(V2, 0);
    }
    
    if (distance <= 150 && distance >=101) {
        Blynk.virtualWrite(V1, 255);
        Blynk.email("sawon78656@gmail.com","Garbage Alert!!!","Box 1!Garbage is filed up by 1/2 portion, would you like to collect?");
        
    }
    
    else {
        Blynk.virtualWrite(V1, 0);
    }
    
     if (distance <= 101 && distance >=0) {
        Blynk.virtualWrite(V0, 255);
        Blynk.email("sawon78656@gmail.com","Garbage Alert!!!","Box 1!No need to collect the garbage.");   
     }
     
     else{
     
        Blynk.virtualWrite(V0, 0);
     }
     //..................................................................................................//
      
    //printing value for serial monitor of dht11
    Serial.print("Current humidity = ");
    Serial.print(hum);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("C  ");
    //printing value for serial monitor of ultrasonic sensor
    Serial.print(distance);
    Serial.println("Centimeter:");
    Blynk.virtualWrite(V5, distance);
    delay(3000);

    //blynk
    Blynk.run();//initiates blynk
    timer.run();//initiates blynk
}

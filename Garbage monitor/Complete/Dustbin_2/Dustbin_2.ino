#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

//give authentication code here
char auth[]="8d8373b120884595b54a006fcbdd6dad";

//give the wifi ssid and password
char ssid[]="Honor_9";
char pass[]="sharoyawn";

//defining gpio pin for ultrasonic sensor
#define TRIGGER 2 //D4 in nodeMCU
#define ECHO    0 //D3 in nodeMCU


void setup(void)
{ 
  Serial.begin(9600); //serial monitor baud rate
  Blynk.begin(auth,ssid,pass); //calling blynk method with parameter

  //setting pin modes for ultrasonic sensor
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() 
{











    //ultrasonic part
    long duration, distance;
    digitalWrite(TRIGGER, LOW);  
    delayMicroseconds(2); 
      
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10); 
      
    digitalWrite(TRIGGER, LOW);
    duration = pulseIn(ECHO, HIGH);
    distance = (duration/2) / 29.1;
    
    if (distance <= 30 && distance >=16){
        Blynk.virtualWrite(V1, 255);
        Blynk.email("sawon78656@gmail.com","Garbage Alert!!!","Box 2!It is high time to collect the garbage.");
        
    }
    
    else {
        Blynk.virtualWrite(V1, 0);
    }
    
    if (distance <= 15 && distance >=0) {
        Blynk.virtualWrite(V0, 255);
        Blynk.email("sawon78656@gmail.com","Garbage Alert!!!","Box 2!no need to collect?");
        
    }
    
    else {
        Blynk.virtualWrite(V0, 0);
    }

     //..................................................................................................//

    //printing value for serial monitor of ultrasonic sensor
    Serial.print(distance);
    Serial.println("Centimeter:");
    Blynk.virtualWrite(V5, distance);
    delay(5000);

    //blynk
    Blynk.run();//initiates blynk
}

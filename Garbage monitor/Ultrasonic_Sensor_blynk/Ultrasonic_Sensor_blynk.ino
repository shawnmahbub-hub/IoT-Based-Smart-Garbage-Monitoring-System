/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#define TRIGGER 2
#define ECHO    0

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "fb4ba8cc723b486d813b946660aef699";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TOTOLINK_N200RE";
char pass[] = "Sharoyawn10661220172";

void setup() {
  
  Serial.begin (9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

   if (distance <= 240) {
    Blynk.virtualWrite(V0, 255);
    Blynk.email("md.mahbub.rahman.shwon@g.bracu.ac.bd","Garbage Alert!!!","You must need to collect the garbage.");
}
  else {
    Blynk.virtualWrite(V0, 0);
  }

 if (distance <= 180) {
    Blynk.virtualWrite(V1, 255);
    Blynk.email("md.mahbub.rahman.shwon@g.bracu.ac.bd","Garbage Alert!!!","It is high time to collect the garbage.");
}
  else {
    Blynk.virtualWrite(V1, 0);
  }

   if (distance <= 120) {
    Blynk.virtualWrite(V2, 255);
    Blynk.email("md.mahbub.rahman.shwon@g.bracu.ac.bd","Garbage Alert!!!","Garbage is filed up by 1/3 portion, would you like to collect?");
}
  else {
    Blynk.virtualWrite(V2, 0);
  }

   if (distance <= 60) {
    Blynk.virtualWrite(V3, 255);
    Blynk.email("md.mahbub.rahman.shwon@g.bracu.ac.bd","Garbage Alert!!!","Garbage bin is filled up by 20%.");
}
  else {
    Blynk.virtualWrite(V3, 0);
  }

   if (distance <= 20) {
    Blynk.virtualWrite(V4, 255);
    Blynk.email("md.mahbub.rahman.shwon@g.bracu.ac.bd","Garbage Alert!!!","Emergency!You must need to collect the garbage.");
}
  else {
    Blynk.virtualWrite(V4, 0);
  }

  
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  Blynk.virtualWrite(V5, distance);
  delay(200);
  Blynk.run();
}

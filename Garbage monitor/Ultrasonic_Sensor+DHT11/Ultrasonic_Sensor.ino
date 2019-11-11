#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11


// DHT Sensor
const int DHTPin = 5;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// defines pins numbers
const int trigPin = 2;  //D3
const int echoPin = 0;  //D2

// defines variables
long duration;
int distance;

void setup() 
{
  //dht11 part
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature \n\n");
  Serial.println("==========================================");
  delay(700);
    
  //ultrasonic part
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() 
{
  //dht11 part.............

    float h = dht.readHumidity();
     float t = dht.readTemperature();         
     
  //ultrasonic part..........
    
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);

  //prints the value of the temperature and humidity
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Serial.println("C  ");
  delay(1000);
}

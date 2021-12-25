#include "DHT.h"
#define DHTTYPE DHT11
int DHTPin  = 4;
DHT dht(DHTPin, DHTTYPE);
float h,t;
void setup(){
  Serial.begin(9600);
  delay(1000);
  pinMode(DHTPin, INPUT);
  dht.begin(); 
}

void loop(){
  delay(1000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\n");
//  exit(0);
}

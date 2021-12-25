#include "BluetoothSerial.h"
const int trigPin = 4;
const int echoPin = 12;
int buzzer = 32;

int range = 10;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
String message = "";
char incomingChar;
BluetoothSerial SerialBT;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
   pinMode(buzzer, OUTPUT);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  digitalWrite(buzzer,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  SerialBT.print("Distance (cm): ");
  SerialBT.println(distanceCm);
  distanceCm = duration * SOUND_SPEED/2;
  
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
      range = message.toInt();
      Serial.print("New Threshold Value:");
      Serial.println(range);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  if( distanceCm < range ){
    digitalWrite(buzzer,HIGH);
    SerialBT.print("yeah its close\n");
    
    }
    else SerialBT.print("far mate!\n");
  
  delay(1000);
}

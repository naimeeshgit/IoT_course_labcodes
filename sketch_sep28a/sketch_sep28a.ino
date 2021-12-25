#include<Servo.h>

Servo motor;
int position;
int incomingByte;
int value;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(13, OUTPUT);
  motor.attach(13);
}

void loop()
{
    if (Serial.available() > 0) 
    {
      incomingByte = Serial.parseInt();

      if(incomingByte > 0)
        {
          value = incomingByte;
          if(value >= 0 && value <= 180)
          {
            motor.write(value);
          }
          Serial.print("I received: ");
          Serial.println(value, DEC);
          delay(1000);
        }
    }
}

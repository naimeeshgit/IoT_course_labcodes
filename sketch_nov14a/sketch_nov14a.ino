const int trigPin = 4;
const int echoPin = 12;
const int buzzerPin = 32;

// define sound speed in cm per microsecond
#define SOUND_SPEED 0.034


int GLOBAL_FLAG = 1;

long duration;
float distanceCm;

float surfaceArea;    // Surface area of the bucket in square cm
float bucketHeight;   // Height of the bucket in cm
float triggerHeight;  // 90% of bucketHeight at which the buzzer is triggered to warn the user

float lastHeight;       // Stores the previous water level in cm for calculating the flow of the water
float flow;             // Stores the increase in water level per loop

float overflowHeight;   // Stores the height the sensor will read when the bucket is full 
int overflowTime;     // Stores the number of milliseconds for which the bucket overflowed
float overflow;         // 1 if bucket has overflown, else 0

float volumeWasted;

String temp;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);    // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT); // Sets the buzzerPin as Output

  digitalWrite(buzzerPin,LOW);  // Sets buzzerPin as LOW initially
  overflowTime = 0;


  // Take Surface Area as input from the user
  Serial.write("Enter approximate surface area of the bucket(in square cm): ");
  
  Serial.flush();

  while(Serial.available() <= 0){

    
  }

   

    
    temp = Serial.readString();
    surfaceArea = temp.toFloat();
    Serial.print("Surface Area is: ");
    Serial.println(surfaceArea, DEC);


    while(Serial.available() <= 0){

    
  }
    
    temp = Serial.readString();
     overflowHeight = temp.toFloat();
    Serial.print("Over flow Height: ");
    Serial.println(overflowHeight, DEC);
  
  
  // Callibrate bucket height
  Serial.println("Hold the sensor at the rim of the bucket to callibrate the height of the bucket");
  Serial.println("Enter any key to callibrate");
  
  while(Serial.available() <= 0) {
     
  }
  
  Serial.println("You will receive the warning when water level reaches 90% of the bucket height");

  
  if (Serial.available() > 0) {
    Serial.read();

    while(Serial.available() > 0) {
      Serial.read();
    }
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the height
    bucketHeight = duration * SOUND_SPEED/2;
    triggerHeight = bucketHeight/2;
  }


}


void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  if(distanceCm <= bucketHeight && GLOBAL_FLAG == 1)
  {
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);




    if(distanceCm <= overflowHeight) {
    overflowTime += 1;
    overflow = 1;
  }

  else 
  { 
    overflow = 0;
    overflowTime = 0;

  }
  


   
  if(distanceCm <= triggerHeight) {  
    digitalWrite(buzzerPin, HIGH);
    Serial.println("WARNING: Bucket about to overflow");

    if (overflow != 1) 
    {
      flow = lastHeight - distanceCm;
      Serial.println(flow);
    }
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }
  

  if(overflow == 1) {
    volumeWasted = overflowTime * flow * surfaceArea;
    Serial.print("Volume of water wasted (in cubic cm) is: ");
    Serial.println(volumeWasted, DEC);
  }

  // This if condition will be executed after the user stops the buzzer or flow of water
  // Currently, this is triggered if the user enters 1 in the Serial Monitor
  if (Serial.available() > 0) {
    int input = (int)(Serial.read() - '0');
    overflow = 0;
    digitalWrite(buzzerPin, LOW);
    // GLOBAL_FLAG = 0;
    // exit(0);
  }
  

  lastHeight = distanceCm;
  delay(500);
  }
  
}

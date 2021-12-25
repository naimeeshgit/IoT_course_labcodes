#include <ThingSpeak.h>
#include<WiFi.h>

#define trigPin 4
#define echoPin 12

// Network information
const char* ssid = "RDJ";
const char* password =  "12345678";

// ThingSpeak information
char* writeAPIKey = "Y2BDJ3BK3BW4FAHH";
char* readAPIKey = "CJWOGVPI3LYN31N5"; 
unsigned long channelID = 1; 

// Global variables
int depth;
int duration;

WiFiClient client; 

void setup() {

   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   Serial.begin(9600);

  // Initialize the output variables as outputs
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);

};

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  depth = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.println(depth);
  ThingSpeak.writeField(channelID,1,depth,writeAPIKey);
  delay(100);
}

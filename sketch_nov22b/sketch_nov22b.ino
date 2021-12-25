#include "PubSubClient.h"
#include"WiFi.h"
#include"ThingSpeak.h"


#define POWER_PIN  15 // ESP32 pin GIOP18 connected to sensor's VCC pin
#define SIGNAL_PIN 4 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin

int value = 0; // variable to store the sensor value

const char* ssid = "RDJ";
const char* password =  "12345678";

char* topic = "channels/1579671/publish/CCGLCMJ1XE0LZO8U"; //channels/<channelID>/publish/API
char* server = "mqtt.thingspeak.com";

WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}


void setup() {
  Serial.begin(115200);
  pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  String clientName="ESP-Thingspeak";
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" as ");
  Serial.println(clientName);
  
  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);
    
    if (client.publish(topic, "hello from ESP32")) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    abort();
  }
}

void loop() {


  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(100);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  Serial.print("Sensor value: ");
  Serial.println(value);

  
//  static int counter = 0;
  String payload="field1=";
  payload+=value;
  payload+="&status=MQTTPUBLISH";
  
  if (client.connected()){
    Serial.print("Sending payload: ");
    Serial.println(value);
    
    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
//  ++counter;
  delay(1000);
}

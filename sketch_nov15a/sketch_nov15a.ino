#include "WiFi.h"
#include "HTTPClient.h"
#include "time.h"
#include <ArduinoJson.h>
char* ssid = "RDJ";
char* password = "12345678";
String cse_ip = "192.168.0.105"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "YOUR_SENSOR_NAME";
String cnt = "Node1";

int usstrigger_pin = 4;
int ussecho_pin = 12;

void createCI(String &val)
{
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
  Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");}
  Serial.println("");
  pinMode(usstrigger_pin, OUTPUT);
  pinMode(ussecho_pin, INPUT);
  
  Serial.println("WiFi connected..!");
}

void loop() {
  digitalWrite(usstrigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(usstrigger_pin, HIGH);  
  delayMicroseconds(10);
  int val = digitalRead(usstrigger_pin);
  String myStr;
  myStr = String(val);
  createCI(myStr);
  delay(500);
}

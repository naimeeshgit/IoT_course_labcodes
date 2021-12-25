#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "smita tiwari 5G";
const char* password = "11223344";
int isTriggered = 0;

const int pir_pin = 4;
bool trig = false;
String data = "";
String page = "";
WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(pir_pin, INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println(WiFi.localIP());

 server.on("/data.txt", [](){
if(isTriggered){
data = "Person Detected!";
}else{
data = "";
}
server.send(200, "text/html", data);
});
server.on("/", [](){
page = "<h1>PIR Sensor to NodeMCU</h1><h1>Data:</h1> <h1 id=\"data\">""</h1>\r\n";
page += "<script>\r\n";
page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
page += "function loadData(url, callback){\r\n";
page += "var xhttp = new XMLHttpRequest();\r\n";
page += "xhttp.onreadystatechange = function(){\r\n";
page += " if(this.readyState == 4 && this.status == 200){\r\n";
page += " callback.apply(xhttp);\r\n";
page += " }\r\n";
page += "};\r\n";
page += "xhttp.open(\"GET\", url, true);\r\n";
page += "xhttp.send();\r\n";
page += "}\r\n";
page += "function updateData(){\r\n";
page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
page += "}\r\n";
page += "</script>\r\n";
server.send(200, "text/html", page);
});

  serial.begin();
  serial.println("Web Server Started");

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(pir_pin);

  if(val==0) {
    trig = false;
  }
  else {
    trig = true;
  }

  server.handleClient();

}

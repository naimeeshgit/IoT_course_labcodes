#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "smita tiwari";  
const char* password = "11223344";  
int pin = 4;
int detected;
String data ="";
String page="";
bool isTriggered;
WebServer server(80);             
 
void setup() {
  pinMode(pin,INPUT);
  Serial.begin(9600);
  delay(500);
  


  Serial.println("Connecting to ");
  Serial.println(ssid);


  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: "); 
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

  
  server.begin();
  Serial.println("HTTP server started");

  
}


void loop(){

  int value = digitalRead(pin);
  if(value==0)
  isTriggered = false;
  else
  isTriggered = true;

  server.handleClient();
}

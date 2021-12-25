#define FEEL 13
#define BUZZ 15

void setup() {
  Serial.begin(115200);
  delay(1000); 
  ledcSetup(0,1E5,18);
  ledcAttachPin(BUZZ,0);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, LOW);
}


void loop() {
  if(touchRead(FEEL)< 20) // 20 is arbitrary threshold val
  {
    ledcWriteTone(0,8000);
  }
}

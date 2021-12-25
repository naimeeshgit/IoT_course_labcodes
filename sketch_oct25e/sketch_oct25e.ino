#define FEEL 13
#define BUZZ 15
#define POW 18
#define SIG 4

int req_water_lev = 1000;
int threshold = 200;
void setup() {
  Serial.begin(9600);
  delay(1000); 
   pinMode(POW, OUTPUT);
  digitalWrite(POW, LOW);
  ledcSetup(0,1E5,18);
  ledcAttachPin(BUZZ,0);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, LOW);
}


void loop() {
  digitalWrite(POW, HIGH); 
  delay(100);
  int ans = analogRead(SIG);
  digitalWrite(POW, LOW);
  if(touchRead(FEEL)< 20) 
  {
    req_water_lev = ans;
  }
  Serial.print("Req water level: ");
  Serial.println(req_water_lev);
  Serial.print("Curr water level: ");
  Serial.println(ans);
  if(req_water_lev > ans)
  {
    if(req_water_lev - ans < threshold)
    {
       digitalWrite(BUZZ, LOW);
       Serial.println("Water Level Fine");

    }
    else
    {
      ledcWriteTone(0,8000);
      Serial.println("Requirement not satisfied");
    }
  }
  else
  {
    if(ans - req_water_lev < threshold)
    { 
      digitalWrite(BUZZ, LOW); 
      Serial.println("Water Level Fine");
    } 
    else
    {
      ledcWriteTone(0,8000);
      Serial.println("Requirement not satisfied");
    } 
  }
  delay(1000);
}

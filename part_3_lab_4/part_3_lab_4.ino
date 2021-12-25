
#define POWER_PIN 18 // ESP32 pin GIOP18 connected to sensor's VCC pin
#define SIGNAL_PIN 4 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin
#define FEEL 13
#define BUZZ 15
int req_level;
int threshhold = 2000;


int value = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT); 
  pinMode(FEEL, INPUT);  
  digitalWrite(POWER_PIN, LOW); 
  
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, LOW);
}

void loop() {

  digitalWrite(POWER_PIN, HIGH);
  Serial.print("Water level is: ");
  int w_level = analogRead(SIGNAL_PIN);
  Serial.println(w_level);
  digitalWrite(POWER_PIN, LOW);
  delay(500);

  Serial.print("TouchValue is: ");
  int touch_val = touchRead(FEEL);
  Serial.println(touch_val);
  delay(500);
  if(value <= 30) {

    req_level = w_level;

    if(req_level >= threshhold)
    {
      digitalWrite(BUZZ, HIGH);
      delay(500);
      digitalWrite(BUZZ, LOW);
    }
    
    
  }
  
}

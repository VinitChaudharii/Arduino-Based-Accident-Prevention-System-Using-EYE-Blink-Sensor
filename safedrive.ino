
#define BLINK_PIN A0
#define BUZZER_PIN 8
#define RELAY_PIN 9

unsigned long blinkStart;
unsigned long blinkDuration;
unsigned long motorStart;

void setup() {
  pinMode(BLINK_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // Check if eye is closed
  if (digitalRead(BLINK_PIN) == HIGH) {
    if (blinkStart == 0) {
      blinkStart = millis();
    }
    blinkDuration = millis() - blinkStart;
    
    // Buzzer on after 4 seconds of eye closure
    if (blinkDuration >= 4000) {
      digitalWrite(BUZZER_PIN, HIGH);
      //digitalWrite(RELAY_PIN, HIGH);  //If want to stop motor at same time
    }
    
    // Motor off after 2 more seconds of eye closure
    if (blinkDuration >= 6000) {
      digitalWrite(RELAY_PIN, HIGH);
      motorStart = millis();
    }
  }
  else {
    blinkStart = 0;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
  }
  
  // Turn off motor after 2 seconds
  if (digitalRead(RELAY_PIN) == HIGH && millis() - motorStart >= 2000) {
    digitalWrite(RELAY_PIN, LOW);
  }
}

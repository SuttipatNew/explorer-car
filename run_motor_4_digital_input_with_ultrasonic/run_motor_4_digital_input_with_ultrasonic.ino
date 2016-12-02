#define echoPin PIN_PC4
#define trigPin PIN_PC5

void setup()
{
  pinMode(PIN_PB2, OUTPUT);
  pinMode(PIN_PB3, OUTPUT);
  pinMode(PIN_PB4, OUTPUT);
  pinMode(PIN_PB5, OUTPUT);
  pinMode(PIN_PC0, INPUT);
  pinMode(PIN_PC1, INPUT);
  pinMode(PIN_PC2, INPUT);
  pinMode(PIN_PC4, INPUT);
  pinMode(PIN_PC5, OUTPUT);
}
 
void loop()
{
  int pin0 = digitalRead(PIN_PC0);
  int pin1 = digitalRead(PIN_PC1);
  int pin2 = digitalRead(PIN_PC2);
  move(pin0, pin1, pin2);
}

void move(int pin0, int pin1, int pin2) {
  if(!pin2 /*|| (findDistance() <= 10 && pin0 && pin1)*/) {
    digitalWrite(PIN_PB2, LOW);
    digitalWrite(PIN_PB3, LOW);
    digitalWrite(PIN_PB4, LOW);
    digitalWrite(PIN_PB5, LOW);
  } else {
    if(pin0 && pin1) {
      digitalWrite(PIN_PB2, HIGH);
      digitalWrite(PIN_PB3, LOW);
      digitalWrite(PIN_PB4, HIGH);
      digitalWrite(PIN_PB5, LOW);
    } else if(!pin0 && !pin1) {
      digitalWrite(PIN_PB2, LOW);
      digitalWrite(PIN_PB3, HIGH);
      digitalWrite(PIN_PB4, LOW);
      digitalWrite(PIN_PB5, HIGH);
    } else if(pin0 && !pin1) {
      digitalWrite(PIN_PB2, LOW);
      digitalWrite(PIN_PB3, HIGH);
      digitalWrite(PIN_PB4, HIGH);
      digitalWrite(PIN_PB5, LOW);
    } else if(!pin0 && pin1) {
      digitalWrite(PIN_PB2, HIGH);
      digitalWrite(PIN_PB3, LOW);
      digitalWrite(PIN_PB4, LOW);
      digitalWrite(PIN_PB5, HIGH);
    }
  }
}

int findDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  int distance= duration*0.034/2;
  return distance;
}


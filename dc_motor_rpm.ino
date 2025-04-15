#define motorA 10
#define motorB 9
#define ENCA 3
#define ENCB 2

volatile long position = 0;
long oldPosition = 0;
unsigned long oldTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  analogWrite(motorA, 100);
  analogWrite(motorB, 0);

  unsigned long newTime = millis();
  long newPosition = position;

  // Calculate RPM
  long deltaPosition = newPosition - oldPosition;
  unsigned long deltaTime = newTime - oldTime;
  float rpm = (deltaPosition / 256.0) * (60000.0 / deltaTime); // Assuming 20 pulses per revolution

  Serial.print("RPM = ");
  Serial.println(rpm);

  oldPosition = newPosition;
  oldTime = newTime;

  delay(250);
}

void readEncoder() {
  int encBval = digitalRead(ENCB);
  if (encBval > 0) {
    position++;
  } else {
    position--;
  }
}

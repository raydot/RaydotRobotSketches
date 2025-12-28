#define TRIG_PIN 12
#define ECHO_PIN 13

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
Serial.println("Ultrasonic sensor ready");
}

void loop() {
  // Send pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  int distance = duration * 0.0133 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" in");

  delay(500);
}

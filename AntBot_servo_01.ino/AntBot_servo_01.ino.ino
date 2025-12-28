#include <Servo.h>

Servo headServo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  headServo.attach(7);
  headServo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Tilt down");
  headServo.write(45);
  delay(2000);

  Serial.println("Tilt up");
  headServo.write(135);
  delay(2000);

  Serial.println("Center");
  headServo.write(90);
  delay(2000);
}

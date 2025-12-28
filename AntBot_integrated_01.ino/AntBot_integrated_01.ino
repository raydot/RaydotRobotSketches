/*
  An all-in-one script to control AntBot
  * Motors
  * Servo
  * Sensor
  * Bluetooth
*/

#include <Servo.h>
#include <SoftwareSerial.h>

// Bluetooth Setup
SoftwareSerial bluetooth(2, 3);

// Motor pins (L298N)
const int IN1 = 5;
const int IN2 = 6;
const int IN3 = 10;
const int IN4 = 11;
const int ENA = 9;
const int ENB = 4;

// Servo
Servo headServo;
const int SERVO_PIN = 7;

// Untrasonic sensor
const int TRIG_PIN = 8;
const int ECHO_PIN = 12;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);

  // Initialize Bluetooth
  bluetooth.begin(9600);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Servo
  headServo.attach(SERVO_PIN);
  headServo.write(90); // Center position

  // Ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Go for robot.");
  bluetooth.println("Go for Bluetooth.");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check for Bluetooth
  if (bluetooth.available()){
    String command = bluetooth.readStringUntil('\n');
    command.trim();
    processCommand(command);
  }

  // Read and send sensor data periodically
  static unsigned long lastSensorRead = 0;
  if (millis() - lastSensorRead > 500) {
    int distance = readDistance();
    bluetooth.print("D: ");
    bluetooth.println(distance);
    lastSensorRead = millis();
  }
}

void processCommand(String cmd) {
  Serial.print("Received: ");
  Serial.println(cmd);

  if (cmd.startsWith("F")) {
    // Forward - extract speed
    int speed = cmd.substring(1).toInt();
    moveForward(speed);
  }
  else if (cmd == "STOP") {
    stopMotors();
  }
  else if (cmd.startsWith("S")) {
    // Servo - extract angle
    int angle = cmd.substring(1).toInt();
    headServo.write(angle);
  }
  else if (cmd.startsWith("L")) {
    // Left turn
    int speed = cmd.substring(1).toInt();
    turnLeft(speed);
  }
  else if (cmd.startsWith("R")) {
    // Right turn
    int speed = cmd.substring(1).toInt();
    turnRight(speed);
  }
  else if (cmd.startsWith("B")) {
    // Backward
    int speed = cmd.substring(1).toInt();
    moveBackward(speed);
  }
}

void moveForward(int speed) {
  // Left motors forward
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motors forward
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void moveBackward(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void turnLeft(int speed) {
  // Left motors backward, right forward
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight(int speed) {
  // Left motors forward, right backward
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  
  analogWrite(ENA, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0);
}

int readDistance() {
  // Send pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH);

  int distance = duration * 0.0133 / 2;

  return distance;
}
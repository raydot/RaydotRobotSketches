// Motor test - both motors forward for 2 seconds and then stop

// Left motor
int IN1 = 5;
int IN2 = 6;
int ENA = 9;

// Right motor
int IN3 = 10;
int IN4 = 11;
int ENB = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  Serial.println("Motors start...");
  // put your main code here, to run repeatedly:
  // Both motors forward at half speed
  // Motor speed (0-255)
  analogWrite(ENA, 128); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 128);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(2000);

  // Stop
  Serial.println("...motors stop.");
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  delay(3000);
}

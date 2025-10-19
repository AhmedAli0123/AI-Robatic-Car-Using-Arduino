// -------------------------------------------------------
// Robot Car with IR Obstacle + Flame Detection + Bluetooth Control
// Wiring based on your setup
// -------------------------------------------------------

// Motor Driver (L298N)
int IN1 = 3;   // Motor A
int IN2 = 4;
int IN3 = 5;   // Motor B
int IN4 = 6;
int ENA = 9;   // Left motor speed (PWM)
int ENB = 10;  // Right motor speed (PWM)

// Sensors
int IR_LEFT = 11;
int IR_RIGHT = 12;
int FLAME_SENSOR = 7;
int BUZZER = 8;

// Bluetooth module (HC-05)
char command = ' ';

// Motor speed (PWM)
int Speed = 200;

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600); // Bluetooth uses hardware serial (D0/D1)
  stopCar();
  digitalWrite(BUZZER, LOW);
}

void loop() {
  // Read sensor values
  int leftIR = digitalRead(IR_LEFT);
  int rightIR = digitalRead(IR_RIGHT);
  int flameDetected = digitalRead(FLAME_SENSOR);

  // ----------------- Auto Stop Logic -----------------
  // IR or flame detection
  if (leftIR == LOW || rightIR == LOW || flameDetected == LOW) {
    stopCar();
    digitalWrite(BUZZER, HIGH); // Alert
    return; // Stop loop temporarily
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // ----------------- Bluetooth Control -----------------
  if (Serial.available() > 0) {
    command = Serial.read();
    handleCommand(command);
  }
}

// ----------------- Command Handler -----------------
void handleCommand(char cmd) {
  switch (cmd) {
    case 'F': forward(); break;
    case 'B': backward(); break;
    case 'L': left(); break;
    case 'R': right(); break;
    case 'S': stopCar(); break;
    // Optional: adjust speed via numbers 0–9
    case '0': Speed = 100; break;
    case '1': Speed = 130; break;
    case '2': Speed = 150; break;
    case '3': Speed = 170; break;
    case '4': Speed = 190; break;
    case '5': Speed = 210; break;
    case '6': Speed = 230; break;
    case '7': Speed = 240; break;
    case '8': Speed = 250; break;
    case '9': Speed = 255; break;
  }
}

// ----------------- Motor Functions -----------------
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

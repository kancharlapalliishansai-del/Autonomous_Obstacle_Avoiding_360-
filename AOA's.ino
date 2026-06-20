// --- PIN DEFINITIONS ---
const int trigF = 2; const int echoF = 3; 
const int trigB = 4; const int echoB = 7; 
const int trigL = 8; const int echoL = 9; 
const int trigR = A0; const int echoR = A1; 
const int buzzer = A2; 
const int enA = 5;  const int in1 = 10; const int in2 = 11; 
const int enB = 6;  const int in3 = 12; const int in4 = 13; 

// --- MANDATORY SETUP FUNCTION ---
void setup() {
  pinMode(trigF, OUTPUT); pinMode(echoF, INPUT);
  pinMode(trigB, OUTPUT); pinMode(echoB, INPUT);
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(enA, OUTPUT); pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  Serial.begin(9600);
}

// --- MANDATORY LOOP FUNCTION ---
void loop() {
  long distF = getDistance(trigF, echoF);

  if (distF > 35) {
    noTone(buzzer);
    moveForward(200); 
  } 
  else if (distF <= 35 && distF > 15) {
    moveForward(100);
    playWarningBeep();
  } 
  else {
    stopMotors();
    tone(buzzer, 1000); 
    delay(500);
    noTone(buzzer);
    navigate(); 
  }
}

// --- SUPPORTING FUNCTIONS ---

long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000); 
  return duration * 0.034 / 2;
}

void playWarningBeep() {
  tone(buzzer, 800);
  delay(40);
  noTone(buzzer);
}

void navigate() {
  moveBackward(150);
  delay(400);
  stopMotors();
  long distL = getDistance(trigL, echoL);
  long distR = getDistance(trigR, echoR);
  if (distL > distR) { turnLeft(180); } 
  else { turnRight(180); }
  delay(500);
  stopMotors();
}

void moveForward(int s) {
  analogWrite(enA, s); analogWrite(enB, s);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void moveBackward(int s) {
  analogWrite(enA, s); analogWrite(enB, s);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void turnLeft(int s) {
  analogWrite(enA, s); analogWrite(enB, s);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void turnRight(int s) {
  analogWrite(enA, s); analogWrite(enB, s);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void stopMotors() {
  analogWrite(enA, 0); analogWrite(enB, 0);
}

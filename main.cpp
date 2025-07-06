// IR Sensor Pins (Analog)
#define IR
LEFT A0
_
#define IR
RIGHT A1
_
// Ultrasonic Sensor Pins
#define TRIG
PIN 11
_
#define ECHO
_
PIN 12 // Digital pin for echo
// L298N Motor Driver Pins
#define BASE
MOTOR
_
_
#define BASE
MOTOR
_
_
#define BASE
MOTOR
IN1 7
IN2 8
_
_
EN 5 // PWM speed control for base motor
#define FAN
#define FAN
#define FAN
MOTOR
_
_
MOTOR
_
_
MOTOR
IN1 9
IN2 4
_
_
EN 6 // PWM speed control for fan blade motor
void setup() {
Serial.begin(9600); // Start Serial Monitor
// IR Sensors
pinMode(IR
_
pinMode(IR
_
LEFT, INPUT);
RIGHT, INPUT);
// Ultrasonic Sensor
pinMode(TRIG
_
pinMode(ECHO
_
PIN, OUTPUT);
PIN, INPUT);
// Motor Driver
pinMode(BASE
pinMode(BASE
pinMode(BASE
MOTOR
_
_
MOTOR
_
_
MOTOR
_
_
IN1, OUTPUT);
IN2, OUTPUT);
EN, OUTPUT);
pinMode(FAN
pinMode(FAN
pinMode(FAN
MOTOR
_
_
MOTOR
_
_
MOTOR
_
_
IN1, OUTPUT);
IN2, OUTPUT);
EN, OUTPUT);
// Initially stop motors
stopBaseMotor();
stopFanMotor();
}
// Function to get distance using the ultrasonic sensor
long getDistance() {
49
digitalWrite(TRIG
_
PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG
_
PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG
_
PIN, LOW);
long duration = pulseIn(ECHO
_
PIN, HIGH);
long distance = duration * 0.034 / 2; // Convert time to distance in cm
return distance;
}
// Rotate Base Left
void rotateBaseLeft() {
digitalWrite(BASE
MOTOR
_
_
digitalWrite(BASE
MOTOR
_
_
analogWrite(BASE
MOTOR
_
_
IN1, HIGH);
IN2, LOW);
EN, 150);
}
// Rotate Base Right
void rotateBaseRight() {
digitalWrite(BASE
MOTOR
_
_
digitalWrite(BASE
MOTOR
_
_
analogWrite(BASE
MOTOR
_
_
IN1, LOW);
IN2, HIGH);
EN, 150);
}
// Stop Base Rotation
void stopBaseMotor() {
digitalWrite(BASE
MOTOR
_
_
digitalWrite(BASE
MOTOR
_
_
analogWrite(BASE
MOTOR
_
_
IN1, LOW);
IN2, LOW);
EN, 0);
}
// Start Fan Motor
void startFanMotor() {
digitalWrite(FAN
MOTOR
_
_
IN1, HIGH);
digitalWrite(FAN
MOTOR
_
_
IN2, LOW);
analogWrite(FAN
MOTOR
_
_
EN, 255); // Full speed
}
// Stop Fan Motor
void stopFanMotor() {
digitalWrite(FAN
digitalWrite(FAN
MOTOR
_
_
MOTOR
_
_
IN1, LOW);
IN2, LOW);
50
analogWrite(FAN
MOTOR
_
_
EN, 0);
}
void loop() {
int left = analogRead(IR
_
LEFT);
int right = analogRead(IR
_
RIGHT);
long distance = getDistance();
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
Serial.print("Left IR: ");
Serial.print(left);
Serial.print(" Right IR: ");
Serial.println(right);
int irThreshold = 100; // IR sensor threshold (adjust if needed)
// --- Base Motor Control (Rotates only based on IR Sensors) ---
if (left < irThreshold && right < irThreshold) {
stopBaseMotor(); // If both IR sensors detect, stop movement
} else if (left < irThreshold) {
rotateBaseLeft(); // If only left IR detects, rotate left
} else if (right < irThreshold) {
rotateBaseRight(); // If only right IR detects, rotate right
} else {
stopBaseMotor(); // Default to stopping
}
// --- Fan Blade Motor Control (Runs only on Ultrasonic Sensor) ---
if (distance >= 10 && distance <= 100) {
startFanMotor(); // Runs continuously in this range
} else {
stopFanMotor(); // Stops if out of range
}
delay(200); // Small delay to prevent rapid switching
}
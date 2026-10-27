// Joystick + SG90 servo + HC-SR04 + LED
// Pins match the breadboard wiring diagram.

#include <Servo.h>

// ---------- Pin definitions ----------
const int JOY_X   = A0;   // joystick VRx
const int JOY_Y   = A1;   // joystick VRy (not used, wired for later)
const int JOY_SW  = 2;    // joystick push button
const int TRIG    = 3;    // HC-SR04 TRIG
const int ECHO    = 4;    // HC-SR04 ECHO
const int LED_PIN = 6;    // LED (through 220 ohm resistor)
const int SERVO_PIN = 9;  // servo signal

// ---------- Settings ----------
const int STOP_DISTANCE = 15;   // cm: stop servo if object is closer
const int RESUME_MARGIN = 3;    // cm: extra gap needed before moving again
const int DEAD_LOW  = 450;      // joystick centre zone
const int DEAD_HIGH = 570;
const int STEP_DELAY = 15;      // ms between servo steps (lower = faster)

Servo myServo;
int angle = 90;
int sweepDir = 1;               // +1 or -1 in auto mode
bool autoMode = false;
bool blocked = false;
bool lastButton = HIGH;
int lastDir = 0;                // direction of the last servo move (+1 / -1)
int blockedDir = 0;             // direction the servo was moving when it got blocked

// Returns distance in cm (999 if no echo)
long readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000UL);  // 30 ms timeout
  if (duration == 0) return 999;
  return duration * 0.0343 / 2;
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(JOY_SW, INPUT_PULLUP);   // button pressed = LOW

  myServo.attach(SERVO_PIN);
  myServo.write(angle);

  Serial.begin(9600);
  Serial.println("Ready. Joystick = manual, press button = toggle auto sweep.");
}

void loop() {
  // ----- Button toggles manual / auto mode -----
  bool button = digitalRead(JOY_SW);
  if (lastButton == HIGH && button == LOW) {
    autoMode = !autoMode;
    Serial.println(autoMode ? "Mode: AUTO sweep" : "Mode: MANUAL joystick");
    delay(200);                    // simple debounce
  }
  lastButton = button;

  // ----- Obstacle check (with hysteresis) -----
  long distance = readDistance();
  if (!blocked && distance < STOP_DISTANCE) {
    blocked = true;
    blockedDir = lastDir;
  } else if (blocked && distance > STOP_DISTANCE + RESUME_MARGIN) {
    blocked = false;
  }
  digitalWrite(LED_PIN, blocked ? HIGH : LOW);

  // ----- Servo control -----
  if (autoMode) {
    // Auto sweep: stops while an obstacle is in front, resumes when it leaves
    if (!blocked) {
      angle += sweepDir;
      if (angle >= 180) { angle = 180; sweepDir = -1; }
      if (angle <= 0)   { angle = 0;   sweepDir = 1;  }
      lastDir = sweepDir;
      myServo.write(angle);
    }
  } else {
    // Manual: when blocked, only moving AWAY from the obstacle is allowed
    int x = analogRead(JOY_X);
    int dir = 0;
    if (x > DEAD_HIGH) dir = 1;
    if (x < DEAD_LOW)  dir = -1;

    if (dir != 0 && !(blocked && dir == blockedDir)) {
      angle = constrain(angle + dir, 0, 180);
      lastDir = dir;
      myServo.write(angle);
    }
  }

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("  Distance: ");
  Serial.print(distance);
  Serial.print(" cm  ");
  Serial.println(blocked ? "OBSTACLE - servo stopped" : "clear");

  delay(STEP_DELAY);
}

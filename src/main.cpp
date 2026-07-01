#include <Arduino.h>
#include <Servo.h>

// Button pin number
const int BUTTON_PIN = 2;

// LED pins
const int GREEN_LED_PIN = 4;
const int YELLOW_LED_PIN = 12;
const int RED_LED_PIN = 13;

// Servo motor pin number
const int SERVO_PIN = 11;

// Global variables
Servo myServo;
int currentState = 0;
bool previousButtonState = HIGH;
int direction = 1;

// Updates the hardware (LEDs and servo) based on the current state
void updateHardware(int state) {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  switch (state) {
  case 0:
    Serial.println("State 0: Green LED / Servo 0 deg");
    digitalWrite(GREEN_LED_PIN, HIGH);
    myServo.write(0);
    break;

  case 1:
    Serial.println("State 1: Yellow LED / Servo 90 deg");
    digitalWrite(YELLOW_LED_PIN, HIGH);
    myServo.write(90);
    break;

  case 2:
    Serial.println("State 2: Red LED / Servo 180 deg");
    digitalWrite(RED_LED_PIN, HIGH);
    myServo.write(180);
    break;
  }
}

// Initializes pins and serial communication
void setup() {
  Serial.begin(9600);
  Serial.println("Starting PiBoard Test...");

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  myServo.attach(SERVO_PIN);

  updateHardware(currentState);
}

// Main loop function. Handles button presses and state transitions
void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (previousButtonState == HIGH && currentButtonState == LOW) {
    currentState += direction;

    if (currentState >= 2) {
      direction = -1;
    } else if (currentState <= 0) {
      direction = 1;
    }

    updateHardware(currentState);
    delay(200); // Debounce
  }

  previousButtonState = currentButtonState;
}

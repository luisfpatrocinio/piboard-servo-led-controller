#include "lcd.h"
#include <Arduino.h>
#include <Servo.h>

// Button pin number
const int BUTTON_PIN = 2; // Pino 2 suporta interrupções externas no Arduino Uno

// LED pins
const int GREEN_LED_PIN = 4;
const int YELLOW_LED_PIN = 12;
const int RED_LED_PIN = 13;

// Servo motor pin number
const int SERVO_PIN = 11;

// Global variables
Servo myServo;
DisplayController oled;

int currentState = 0;
int direction = 1;

// Variáveis para a Interrupção (ISR)
volatile bool buttonPressedFlag = false;
volatile unsigned long lastInterruptTime = 0;

// Rotina de Serviço de Interrupção (ISR) do Botão
void buttonISR() {
  unsigned long interruptTime = millis();
  // Debounce direto na interrupção (ignora ruídos < 200ms)
  if (interruptTime - lastInterruptTime > 200) {
    buttonPressedFlag = true;
    lastInterruptTime = interruptTime;
  }
}

// Updates the hardware (LEDs, servo, and display) based on the current state
void updateHardware(int state) {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  const __FlashStringHelper* ledName = nullptr;
  int servoAngle = 0;

  switch (state) {
  case 0:
    Serial.println(F("State 0: Green LED / Servo 0 deg"));
    digitalWrite(GREEN_LED_PIN, HIGH);
    servoAngle = 0;
    ledName = F("Verde");
    break;

  case 1:
    Serial.println(F("State 1: Yellow LED / Servo 90 deg"));
    digitalWrite(YELLOW_LED_PIN, HIGH);
    servoAngle = 90;
    ledName = F("Amarelo");
    break;

  case 2:
    Serial.println(F("State 2: Red LED / Servo 180 deg"));
    digitalWrite(RED_LED_PIN, HIGH);
    servoAngle = 180;
    ledName = F("Vermelho");
    break;
  }

  myServo.write(servoAngle);
  
  // Atualiza o display instantaneamente via a classe DisplayController
  oled.showState(direction, ledName);
}

// Initializes pins and serial communication
void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting PiBoard Test..."));

  // Inicializa a classe DisplayController
  oled.begin();
  oled.showWelcomeMessage();

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Configura o pino com pullup e anexa a interrupção de hardware na borda de descida (FALLING)
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  myServo.attach(SERVO_PIN);

  // Coloca o hardware no estado inicial e já atualiza o display
  updateHardware(currentState);

  Serial.println(F("Setup Done!"));
}

// Main loop function. Handles button presses non-blockingly
void loop() {
  // Verifica se a interrupção de hardware detectou um clique válido
  if (buttonPressedFlag) {
    buttonPressedFlag = false; // Limpa a flag

    currentState += direction;

    if (currentState >= 2) {
      direction = -1;
    } else if (currentState <= 0) {
      direction = 1;
    }

    updateHardware(currentState);

    Serial.print(F("State: "));
    Serial.println(currentState);
  }
}

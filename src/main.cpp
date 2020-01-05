#include <Arduino.h>
#include <ESP8266WiFi.h>

#define PIN0 16
#define PIN1 5
#define PIN2 4
#define PIN3 14
#define PIN4 12
#define PIN5 13
#define PIN6 0
#define PIN7 2

#define PIN_RX 3

bool serialModeEnabled = false;
int pins[] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7};

void turnOnAll() {
  digitalWrite(PIN0, HIGH);
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, HIGH);
  digitalWrite(PIN5, HIGH);
  digitalWrite(PIN6, HIGH);
  digitalWrite(PIN7, HIGH);
}

void turnOff() {
  digitalWrite(PIN0, LOW);
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, LOW);
  digitalWrite(PIN5, LOW);
  digitalWrite(PIN6, LOW);
  digitalWrite(PIN7, LOW);
}

void turnOn(int i) {
  digitalWrite(pins[i], HIGH);
}

void setup() {
  pinMode(PIN_RX, INPUT);
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  pinMode(PIN5, OUTPUT);
  pinMode(PIN6, OUTPUT);
  pinMode(PIN7, OUTPUT);

  turnOff();
  Serial.begin(9600);
}

int cycle = 0;
void loop() {
  if (Serial.available() > 0) {
    serialModeEnabled = true;
    int incomingByte = Serial.read();
    if (incomingByte > 0) {
      turnOff();
      int pin = incomingByte % 8;
      turnOn(pin);
    }
  }

  if (!serialModeEnabled) {
    if(cycle < 8) {
      turnOff();
      turnOn(cycle++);
      delay(1000);
    } else {
      turnOnAll();
      delay(1000);
      turnOff();
      delay(1000);
      cycle = 0;
    }
  }
}
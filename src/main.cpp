#include <Arduino.h>

#define PIN_RX 0

bool serialModeEnabled = false;
int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void turnOnAll() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void turnOff() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void turnOn(int i) {
  digitalWrite(pins[i], HIGH);
}

void setup() {
  pinMode(PIN_RX, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

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
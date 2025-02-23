#include "button.h"

#define LED1_PIN 2
#define LED2_PIN 3
#define BUTTON1_PIN 4
#define BUTTON2_PIN 5
#define UNDEFINED -1
#define OFF_TIME 10000

Room room1 = { BUTTON1_PIN, LED1_PIN, LOW, HIGH };
Room room2 = { BUTTON2_PIN, LED2_PIN, LOW, HIGH };

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");

  pinMode(room1.buttonPin, INPUT_PULLUP);
  pinMode(room2.buttonPin, INPUT_PULLUP);
  pinMode(room1.ledPin, OUTPUT);
  pinMode(room2.ledPin, OUTPUT);

  digitalWrite(room1.ledPin, HIGH);
  digitalWrite(room2.ledPin, HIGH);

  doorState(room1);
  doorState(room2);
}

inline void doorState(Room &room) {
  int level = digitalRead(room.buttonPin);

  if (level == HIGH) {
    room.lastLevel = UNDEFINED;
  }
}

void loop() {
  function(room1);
  function(room2);
}

void function(Room &room) {
  int level = digitalRead(room.buttonPin);

  if (level == HIGH && level != room.lastLevel && room.lastLevel != UNDEFINED) {
    room.light = room.light == HIGH ? LOW : HIGH;
    digitalWrite(room.ledPin, room.light);

    if(room.light == HIGH){
      room.timeOff = millis();
    }
  }

  if (room.light == LOW && room.timeOff > 0 && (millis() - room.timeOff >= OFF_TIME)) {
    room.light = HIGH;
    digitalWrite(room.ledPin, HIGH);
    room.timeOff = 0; 
}

  room.lastLevel = level;
}
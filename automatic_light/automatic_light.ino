#include "button.h"

#define LED1_PIN 2
#define LED2_PIN 3
#define BUTTON1_PIN 4
#define BUTTON2_PIN 5

Button button1 = { BUTTON1_PIN, 0, HIGH, LED1_PIN };
Button button2 = { BUTTON2_PIN, 0, HIGH, LED2_PIN };

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");

  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);
  pinMode(button1.ledPin, OUTPUT);
  pinMode(button2.ledPin, OUTPUT);

  digitalWrite(button1.ledPin, HIGH);
  digitalWrite(button2.ledPin, HIGH);
}

void loop() {
  function(button1);
 // function(button2);
}

void function(Button &button) {
    bool level = digitalRead(button.pin);

    if (level == LOW && button.lastState == HIGH) {  
        button.pressCount++;  
        if (button.pressCount > 3) {
            button.pressCount = 0;  
        }

        Serial.print("Button pressed, count: ");
        Serial.println(button.pressCount);
    }

    switch (button.pressCount) {
        case 0:
        case 3:
            digitalWrite(button.ledPin, LOW);  
            break;
        case 1:
        case 2:
            digitalWrite(button.ledPin, HIGH); 
            break;
    }

    button.lastState = level;
    delay(50); 
}







struct Button {
  int pin;
  int pressCount;
  bool lastState;
};

enum State {
  OFF = LOW,
  ON = HIGH
};

#define LED1_PIN 2
#define LED2_PIN 3
#define BUTTON1_PIN 4
#define BUTTON2_PIN 5

Button button1 = { BUTTON1_PIN, 0, HIGH };
Button button2 = { BUTTON2_PIN, 0, HIGH };

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  function(button1, LED1_PIN);
  function(button2, LED2_PIN);
}

void function(Button &button, int ledPin) {

  int level = digitalRead(button.pin);

  if (level == LOW && button.lastState == HIGH) {
    button.pressCount++;
    Serial.println("Pressed a button");
  }

  if (level == HIGH && button.lastState == LOW && button.pressCount == 2) {
    digitalWrite(ledPin, ON);
    Serial.println("Level1 low");
    button.pressCount = 0;
  }
  button.lastState = level;
}
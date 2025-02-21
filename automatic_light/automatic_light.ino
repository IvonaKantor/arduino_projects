struct Button {
  int pin;
  int pressCount;
  bool lastState;
  int ledPin;
};

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

  digitalWrite(button1.ledPin, LOW);
  digitalWrite(button2.ledPin, LOW);
}

void loop() {
  function(button1);
  function(button2);
}

void function(Button &button) {
  bool level = digitalRead(button.pin);

  if (level == LOW && button.lastState == HIGH) {
    button.pressCount = (button.pressCount + 1) % 4;
    Serial.print("Button ");
    Serial.print(button.pin);
    Serial.print(" pressed, count: ");
    Serial.println(button.pressCount);
    delay(500);
  }

  if (button.pressCount == 1) {
    digitalWrite(button.ledPin, HIGH);
  }else if(button.pressCount == 3){
    digitalWrite(button.ledPin, LOW);
  }

  button.lastState = level;
}

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

  digitalWrite(LED1_PIN, ON);
  digitalWrite(LED2_PIN, ON);
}

void loop() {
  function(button1, LED1_PIN);
  function(button2, LED2_PIN);
}

void function(Button &button, int ledPin) {

  bool level = digitalRead(button.pin);

  if (level == LOW && button.lastState == HIGH) {
    delay(50);
    button.pressCount++;
    Serial.println("Pressed a button");
  }

  if (level == HIGH && button.lastState == LOW) {
    if(button.pressCount == 2){
    digitalWrite(ledPin, ON);
    Serial.println("Led was turned ON ");
    Serial.print(ledPin);
    button.pressCount = 0;
    }
  }
  button.lastState = level;
}
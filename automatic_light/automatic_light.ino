struct Button{
  int pin;
  int pressCount;
  bool lastState;
};

enum State{
  OFF = LOW,
  ON = HIGH
};

#define LED1_PIN 2
#define LED2_PIN 3
#define BUTTON1_PIN 4
#define BUTTON2_PIN 5

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  static int pressCount1 = 0;
  static int pressCount2 = 0;
  static bool state1 = HIGH;
  static bool state2 = HIGH;
  int level1 = digitalRead(button1);
  int level2 = digitalRead(button2);

  if (level1 == LOW && state1 == HIGH) {
    pressCount1++;
    Serial.println("Pressed button1");
  }

  if (level1 == HIGH && state1 == LOW && pressCount1 == 2) {
    digitalWrite(led1, HIGH);
    Serial.println("Level1 low");
    pressCount1 = 0;
  } 
  state1 = level1;

  if (level2 == LOW && state2 == HIGH) {
    pressCount2++;
    Serial.println("Pressed button2");
  }

  if (level2 == HIGH && state2 == LOW && pressCount2 == 2) {
    digitalWrite(led2, HIGH);
    Serial.println("Level2 low");
    pressCount2 = 0;
  }
  state2 = level2;
}
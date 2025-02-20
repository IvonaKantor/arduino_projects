#define button1 4
#define button2 5
#define led1 2
#define led2 3

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  int level1 = digitalRead(button1);
  int level2 = digitalRead(button2);

  if(level1 == LOW){
    digitalWrite(led1, HIGH);
  }
  else if(level2 == LOW){
    digitalWrite(led2, HIGH);
  }
}

#define RELAY_PIN_1 2
#define RELAY_PIN_2 3
#define SENSOR_PIN_1 4
#define SENSOR_PIN_2 5
#define AUTO_OFF_DISABLE_PIN 12
#define INVALID_TIME -1
#define AUTO_OFF_DELAY_MS 3600000

enum DoorState {
  DOOR_CLOSED,
  DOOR_OPENED
};

struct Room {
  int sensorPin;
  int relayPin;
  unsigned long autoOffTime = INVALID_TIME;
  DoorState currentDoorState;
  bool isPersonInside = false;
};

Room room1;
Room room2;
bool isAutoOffEnabled = false;

void setup() {

  room1.sensorPin = SENSOR_PIN_1;
  room1.relayPin = RELAY_PIN_1;
  room1.currentDoorState = (DoorState)digitalRead(room1.sensorPin);

  room2.sensorPin = SENSOR_PIN_2;
  room2.relayPin = RELAY_PIN_2;
  room2.currentDoorState = (DoorState)digitalRead(room2.sensorPin);

  pinMode(room1.sensorPin, INPUT_PULLUP);
  pinMode(room2.sensorPin, INPUT_PULLUP);
  pinMode(AUTO_OFF_DISABLE_PIN, INPUT_PULLUP);

  pinMode(room1.relayPin, OUTPUT);
  pinMode(room2.relayPin, OUTPUT);

  digitalWrite(room1.relayPin, HIGH);
  digitalWrite(room2.relayPin, HIGH);

  isAutoOffEnabled = digitalRead(AUTO_OFF_DISABLE_PIN);
}

void loop() {
  updateRoomState(room1);
  updateRoomState(room2);
}

void updateRoomState(Room &room) {
  DoorState currentSensorState = (DoorState)digitalRead(room.sensorPin);

  if (currentSensorState != room.currentDoorState) {
    if (currentSensorState == DoorState::DOOR_OPENED && !room.isPersonInside) {
      turnOnLight(room);
    } else if (currentSensorState == DoorState::DOOR_OPENED && room.isPersonInside) {
      personLeft(room);
    } else if (currentSensorState == DoorState::DOOR_CLOSED && !room.isPersonInside) {
      turnOffLight(room);
    }
    delay(200);
  }

  if (isAutoOffEnabled && room.autoOffTime != INVALID_TIME && millis() >= room.autoOffTime) {
    turnOffLight(room);
    personLeft(room);
  }

  room.currentDoorState = currentSensorState;
}

inline void turnOffLight(Room &room) {
  digitalWrite(room.relayPin, HIGH);
  room.autoOffTime = INVALID_TIME;
}

inline void turnOnLight(Room &room) {
  digitalWrite(room.relayPin, LOW);
  room.autoOffTime = millis() + AUTO_OFF_DELAY_MS;
  personEntered(room);
}

inline void personEntered(Room &room) {
  room.isPersonInside = true;
}

inline void personLeft(Room &room) {
  room.isPersonInside = false;
}
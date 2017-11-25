const int LED_PORT = 13;
const int MOTOR_PORT = 2;
const int SENSOR_PORT = A0;

// Declare humidity limits (the lower the more humid)
const int LIMIT_HIGHT_HUMIDTY = 400;
const int LIMIT_LOW_HUMIDITY = 800; // dryness limit

void setup() {
  pinMode(LED_PORT, OUTPUT);
  pinMode(MOTOR_PORT, OUTPUT);
  pinMode(SENSOR_PORT, INPUT);

  Serial.begin(9600);
}

void loop() {
  if (canIrrigate(LIMIT_LOW_HUMIDITY)) {
    irrigate(LIMIT_HIGHT_HUMIDTY);
  }

  Serial.println(analogRead(SENSOR_PORT));
  delay(1000);
}

bool canIrrigate(int min_humidity) {
  if (analogRead(SENSOR_PORT) > min_humidity) {
    return true;
  }

  return false;
}

// Turns irrigation on until max_humidity reached
void irrigate(int max_humidity) {
  Serial.print("Last read: ");
  Serial.println(analogRead(SENSOR_PORT));
  Serial.println("Irrigating!");

  while (analogRead(SENSOR_PORT) > max_humidity) {
    digitalWrite(MOTOR_PORT, HIGH);
    digitalWrite(LED_PORT, HIGH);
  }

  digitalWrite(MOTOR_PORT, LOW);
  digitalWrite(LED_PORT, LOW);
}

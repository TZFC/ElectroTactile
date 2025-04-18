#define TRAN_PIN_TOP_LEFT 3
#define TRAN_PIN_TOP_RIGHT 5
#define TRAN_PIN_BOT_LEFT 6
#define TRAN_PIN_BOT_RIGHT 9 
#define LED_PIN 11

void setup() {
  pinMode(TRAN_PIN_TOP_LEFT, OUTPUT);
  pinMode(TRAN_PIN_TOP_RIGHT, OUTPUT);
  pinMode(TRAN_PIN_BOT_LEFT, OUTPUT);
  pinMode(TRAN_PIN_BOT_RIGHT, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void stimulate(int pin, int time_ms) { // time in milliseconds
  int pulses = time_ms / 20; // 50Hz → 20ms per cycle
  for (int i = 0; i < pulses; i++) {
    digitalWrite(pin, HIGH);
    delay(10);  // 10ms pulse
    digitalWrite(pin, LOW);
    delay(10);  // 10ms rest → 20ms total
  }
}

void loop() {
  digitalWrite(LED_PIN, HIGH);

  stimulate(TRAN_PIN_TOP_LEFT, 1000);
  stimulate(TRAN_PIN_TOP_RIGHT, 1000);

  delay(1000);

  stimulate(TRAN_PIN_BOT_LEFT, 1000);
  stimulate(TRAN_PIN_BOT_RIGHT, 1000);

  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

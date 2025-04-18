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

  Serial.begin(9600); 
}

int pinToGridIndex(int pin) {
  switch(pin) {
    case TRAN_PIN_TOP_LEFT: return 0;   
    case TRAN_PIN_TOP_RIGHT: return 1;  
    case TRAN_PIN_BOT_LEFT: return 2;  
    case TRAN_PIN_BOT_RIGHT: return 3;  
    default: return -1;
  }
}

void printElectrodeGrid(const int pins[], int count) {
  int grid[2][2] = {{0, 0}, {0, 0}};

  for (int i = 0; i < count; i++) {
    int index = pinToGridIndex(pins[i]);
    if (index == 0) grid[0][0] = 1;
    else if (index == 1) grid[0][1] = 1;
    else if (index == 2) grid[1][0] = 1;
    else if (index == 3) grid[1][1] = 1;
  }

  Serial.println("Electrode activation map:");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print(grid[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void stimulateCombo(const int pins[], const char* labels[], int count, int time_ms) {
  printElectrodeGrid(pins, count);  // show visual map

  int pulses = time_ms / 20; // 50 Hz
  for (int i = 0; i < pulses; i++) {
    for (int j = 0; j < count; j++) digitalWrite(pins[j], HIGH);
    delay(10);
    for (int j = 0; j < count; j++) digitalWrite(pins[j], LOW);
    delay(10);
  }
}

void loop() {
  digitalWrite(LED_PIN, HIGH);

  const int combo1[] = {TRAN_PIN_TOP_LEFT, TRAN_PIN_TOP_RIGHT};
  const char* labels1[] = {"Top Left", "Top Right"};
  stimulateCombo(combo1, labels1, 2, 1000);

  delay(1000);  

  const int combo2[] = {TRAN_PIN_BOT_LEFT, TRAN_PIN_BOT_RIGHT};
  const char* labels2[] = {"Bottom Left", "Bottom Right"};
  stimulateCombo(combo2, labels2, 2, 1000);

  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

// void stimulate(int pin, int time_ms, const char* label) { // time in milliseconds

//   Serial.print("Stimulating ");
//   Serial.println(label);

//   int pulses = time_ms / 20; // 50Hz → 20ms per cycle
//   for (int i = 0; i < pulses; i++) {
//     digitalWrite(pin, HIGH);
//     delay(10);  // 10ms pulse
//     digitalWrite(pin, LOW);
//     delay(10);  // 10ms rest → 20ms total
//   }
// }

// void loop() {
//   digitalWrite(LED_PIN, HIGH);

//   stimulate(TRAN_PIN_TOP_LEFT, 1000, "Top Left");
//   stimulate(TRAN_PIN_TOP_RIGHT, 1000, "Top Right");

//   delay(1000);

//   stimulate(TRAN_PIN_BOT_LEFT, 1000, "Bottom Left");
//   stimulate(TRAN_PIN_BOT_RIGHT, 1000, "Bottom Right");


//   digitalWrite(LED_PIN, LOW);
//   delay(1000);
// }

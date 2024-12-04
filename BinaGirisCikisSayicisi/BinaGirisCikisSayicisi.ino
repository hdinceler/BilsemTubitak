#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library

// Pin definitions
#define ldrA 2
#define ldrB 3
#define btnReset 4
#define buzzerPin 11
#define beepTime 50
#define SHOW_SERIAL false
// LCD initialization (address: 0x27, 20 columns, 4 rows)
LiquidCrystal_I2C lcd(0x27, 20, 4);  

uint8_t ldrA_activated = false;
uint8_t ldrB_activated = false;
unsigned long counter = 0;

// Time and state variables
unsigned long lastLdrTime = 0; // Last activation time
const unsigned long debounceDelay = 100; // Minimum delay (ms)

// Sequence control variable
enum LastActivated { NONE, LDR_A, LDR_B };
LastActivated lastActivated = NONE; // Tracks which LDR was last activated

void setup() {
  if(SHOW_SERIAL) Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrA, INPUT);
  pinMode(ldrB, INPUT);
  digitalWrite(buzzerPin, LOW);

  // Reset button setup
  pinMode(btnReset, INPUT_PULLUP);

  // LCD setup
  lcd.init();               // Initialize the LCD
  lcd.backlight();          // Turn on the backlight
}

void loop() {
  count();         // Update the counter
  if(SHOW_SERIAL) Serial.print("Counter: ");
  if(SHOW_SERIAL) Serial.println(counter);

  // Display the counter value on the LCD
  //lcd.clear();             // Clear the LCD screen
  lcd.setCursor(0, 0);     // Set cursor to first column, first row
  lcd.print("Mevcut: ");   // Print text

  // Print the counter as a 9-digit value with leading spaces
  lcd.setCursor(7, 1);     // Move the cursor to display the counter value
  printFormattedCounter(counter);  // Function to display counter with leading spaces
}

// Function to print the counter value as 9 digits, aligned to the right
void printFormattedCounter(unsigned long counter) {
  char formattedCounter[10];  // Array to hold the formatted counter as a string
  sprintf(formattedCounter, "%9lu", counter);  // Format the counter with leading spaces
  lcd.print(formattedCounter);  // Print the formatted counter
}

void count() {
  if (digitalRead(btnReset) == LOW) {
    counter = 0;
    playResetTone(); // Play reset tone
    delay(500); // Short delay to avoid accidental multiple resets
}
  unsigned long currentTime = millis();

  // If both LDRs are activated at the same time, do nothing
  if (digitalRead(ldrA) == HIGH && digitalRead(ldrB) == HIGH) {
    return; // Stop processing
  }

  // If LDR A is activated
  if (digitalRead(ldrA) == HIGH && lastActivated != LDR_A && currentTime - lastLdrTime > debounceDelay) {
    ldrA_activated = true;
    lastActivated = LDR_A; // Last activated LDR is A
    lastLdrTime = currentTime;
  }

  // If LDR B is activated
  if (digitalRead(ldrB) == HIGH && lastActivated != LDR_B && currentTime - lastLdrTime > debounceDelay) {
    ldrB_activated = true;
    lastActivated = LDR_B; // Last activated LDR is B
    lastLdrTime = currentTime;
  }

  // If LDR A is activated before LDR B, count as an entry
  if (ldrA_activated && lastActivated == LDR_B) {
    counter++; // Increase the counter
    playEntryTone(); // Play entry tone
    resetLDRStates();
  }

  // If LDR B is activated before LDR A, count as an exit
  if (ldrB_activated && lastActivated == LDR_A) {
    if (counter > 0) { // Prevent the counter from going below 0
      counter--; // Decrease the counter
      playExitTone(); // Play exit tone
    }
    resetLDRStates();
  }
}

// Reset LDR states
void resetLDRStates() {
  ldrA_activated = false;
  ldrB_activated = false;
  lastActivated = NONE;
}

// Play entry tone (for entry)
void playEntryTone() {
  tone(buzzerPin, 440, beepTime); // La note, 200ms
  delay(beepTime);
  tone(buzzerPin, 523, beepTime); // Do note, 200ms
  delay(beepTime);
  tone(buzzerPin, 659, beepTime); // Mi note, 200ms
  delay(beepTime);
  noTone(buzzerPin);
}

// Play exit tone (for exit)
void playExitTone() {
  tone(buzzerPin, 659, beepTime); // Mi note, 200ms
  delay(beepTime);
  tone(buzzerPin, 523, beepTime); // Do note, 200ms
  delay(beepTime);
  tone(buzzerPin, 440, beepTime); // La note, 200ms
  delay(beepTime);
  noTone(buzzerPin);
}

// Play reset tone
void playResetTone() {
  tone(buzzerPin, 349, beepTime); delay(beepTime); // Fa note
  tone(buzzerPin, 440, beepTime); delay(beepTime); // La note
  tone(buzzerPin, 523, beepTime); delay(beepTime); // Do note
  tone(buzzerPin, 440, beepTime); delay(beepTime); // La note
  tone(buzzerPin, 349, beepTime); delay(beepTime); // Fa note
  noTone(buzzerPin);  // Stop the tone
}

#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

int hours = 11;     // Start time hours (set your current hour here)
int minutes = 7;    // Start time minutes (set your current minute here)
int seconds = 0;    // Start from 0 seconds
bool showColon = true;

unsigned long previousMillis = 0;
const long interval = 1000; // 1 second

void setup() {
  display.setBrightness(7); // Brightness level 0–7
  Serial.begin(9600);       // ✅ Start Serial Monitor
  Serial.println("Digital Clock Simulation Started");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update seconds
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) hours = 0;
      }
    }

    // Toggle colon every second (like a real clock)
    showColon = !showColon;

    // Format time as HHMM
    int time = hours * 100 + minutes;

    // Display with or without colon
    if (showColon) {
      display.showNumberDecEx(time, 0b01000000, true); // Colon ON
    } else {
      display.showNumberDecEx(time, 0b00000000, true); // Colon OFF
    }

    // ✅ Print to Serial Monitor
    Serial.print("Time -> ");
    if (hours < 10) Serial.print("0");
    Serial.print(hours);
    Serial.print(":");
    if (minutes < 10) Serial.print("0");
    Serial.print(minutes);
    Serial.print(":");
    if (seconds < 10) Serial.print("0");
    Serial.println(seconds);
  }
}

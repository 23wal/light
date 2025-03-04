#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// EEPROM
#define EEPROM_SIZE 4

// Function to write an integer to EEPROM
void writeIntToEEPROM(int address, int value) {
  EEPROM.put(address, value); // Write the integer to the given address
  EEPROM.commit();            // Save changes to flash
}

// Function to read an integer from EEPROM
int readFromEEPROM(int address) {
  int value = 0;
  EEPROM.get(address, value); // Read the integer from the given address
  return value;
}

void selectChannel() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("CHANNEL:");
  display.setCursor(40, 30);
  display.setTextSize(3);
  display.println(String(readFromEEPROM(0)));
  display.display();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  // initialize the OLED object
  Wire.begin(4, 5); // SDA to GPIO4, SCL to GPIO5
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  Serial.println(F("SSD1306 allocation succeed"));
  // Write an integer to EEPROM
  /*int valueToWrite = 511; // Example integer*/
  /*writeIntToEEPROM(0, valueToWrite);*/
  /*Serial.print("Written value: ");*/
  /*Serial.println(valueToWrite);*/

  // Clear the buffer.
  display.clearDisplay();

  // Changing Font Size
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("DMX2VGA");
  display.display();
  delay(2000);
  // display.clearDisplay();
  selectChannel();
}

void loop() {}

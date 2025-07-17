#include <Arduino.h>

#define DMX_RX_PIN 3  // GPIO3 (RX) for ESP8266
#define DMX_BAUD 250000  // Standard DMX baud rate
#define DMX_CHANNELS 512  // Maximum DMX channels

uint8_t dmxData[DMX_CHANNELS + 1];  // DMX buffer (1-based index)
int currentChannel = 0;
bool receivingDmx = false;

void setup() {
    Serial.begin(115200);  // Debugging output
    Serial.setRxBufferSize(DMX_CHANNELS + 1);  // Increase buffer for DMX data
    Serial.begin(DMX_BAUD, SERIAL_8N2);  // Start DMX receiving on GPIO3 (RX)
    Serial.println("DMX Receiver Ready");
}

void loop() {
    static uint32_t lastByteTime = 0;
    static bool newFrame = true;

    while (Serial.available()) {
        uint8_t incomingByte = Serial.read();
        uint32_t now = micros();

        // Serial.println(incomingByte);
        // If no data received for >100us, it's a new DMX frame
        if (now - lastByteTime > 200) {
            newFrame = true;
            receivingDmx = false;
        }

        if (newFrame) {
            if (incomingByte == 0x00) {  // Start Code detected
                newFrame = false;
                receivingDmx = true;
                currentChannel = 1;  // Start at channel 1
            }
        } else if (receivingDmx) {
            if (currentChannel <= DMX_CHANNELS) {
                dmxData[currentChannel] = incomingByte;

                // Print value ONLY if it changes
                static uint8_t lastValues[DMX_CHANNELS + 1] = {0};
                if (dmxData[currentChannel] != lastValues[currentChannel]) {
                    Serial.printf("DMX Channel %d: %d\n", currentChannel, dmxData[currentChannel]);
                    lastValues[currentChannel] = dmxData[currentChannel];
                }
                currentChannel++;
            }
        }

        lastByteTime = now;
    }
}

// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <Arduino.h>
// #include <EEPROM.h>
// #include <Wire.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define SCREEN_ADDRESS 0x3C
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// // EEPROM
// #define EEPROM_SIZE 4

// // Function to write an integer to EEPROM
// void writeIntToEEPROM(int address, int value) {
//   EEPROM.put(address, value); // Write the integer to the given address
//   EEPROM.commit();            // Save changes to flash
// }

// // Function to read an integer from EEPROM
// int readFromEEPROM(int address) {
//   int value = 0;
//   EEPROM.get(address, value); // Read the integer from the given address
//   return value;
// }

// void selectChannel() {
//   display.clearDisplay();
//   display.setCursor(0, 0);
//   display.setTextSize(2);
//   display.println("CHANNEL:");
//   display.setCursor(40, 30);
//   display.setTextSize(3);
//   display.println(String(readFromEEPROM(0)));
//   display.display();
// }

// void setup() {
//   Serial.begin(115200);
//   EEPROM.begin(EEPROM_SIZE);

//   // initialize the OLED object
//   Wire.begin(4, 5); // SDA to GPIO4, SCL to GPIO5
//   if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for (;;)
//       ; // Don't proceed, loop forever
//   }
//   Serial.println(F("SSD1306 allocation succeed"));
//   // Write an integer to EEPROM
//   /*int valueToWrite = 511; // Example integer*/
//   /*writeIntToEEPROM(0, valueToWrite);*/
//   /*Serial.print("Written value: ");*/
//   /*Serial.println(valueToWrite);*/

//   // Clear the buffer.
//   display.clearDisplay();

//   // Changing Font Size
//   display.setTextColor(WHITE);
//   display.setCursor(0, 0);
//   display.setTextSize(2);
//   display.println("DMX2VGA");
//   display.display();
//   delay(2000);
//   // display.clearDisplay();
//   selectChannel();
// }

// void loop() {}

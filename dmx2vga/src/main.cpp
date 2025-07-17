#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

// DISPLAY
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DMX
#define DMX_RX_PIN 3     // GPIO3 (RX) for ESP8266
#define DMX_BAUD 250000  // Standard DMX baud rate
#define DMX_CHANNELS 512 // Maximum DMX channels

uint8_t dmxData[DMX_CHANNELS + 1]; // DMX buffer (1-based index)
int currentChannel = 0;
bool receivingDmx = false;

unsigned long lastDisplayUpdate = 0; // Timer for display update
const unsigned long displayInterval = 100;

void setup() {
  Wire.begin(4, 5); // SDA to GPIO4, SCL to GPIO5
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  Serial.begin(115200);                     // Debugging output
  Serial.setRxBufferSize(DMX_CHANNELS + 1); // Increase buffer for DMX data
  Serial.begin(DMX_BAUD, SERIAL_8N2);       // Start DMX receiving on GPIO3 (RX)
  Serial.println("DMX Receiver Ready");

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("DMX2VGA");
  display.display();
  delay(2000);
}

void updateDisplay(int channel, int value) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("CHANNEL:" + String(channel));
  display.setCursor(40, 30);
  display.setTextSize(3);
  display.println(String(value));
  display.display();
}

void loop() {
  static uint32_t lastByteTime = 0;
  static bool newFrame = true;

  while (Serial.available()) {
    uint8_t incomingByte = Serial.read();
    uint32_t now = micros();

    // If no data received for >200us, it's a new DMX frame
    if (now - lastByteTime > 200) {
      newFrame = true;
      receivingDmx = false;
    }

    if (newFrame) {
      if (incomingByte == 0x00) { // Start Code detected
        newFrame = false;
        receivingDmx = true;
        currentChannel = 1; // Start at channel 1
      }
    } else if (receivingDmx) {
      if (currentChannel <= DMX_CHANNELS) {
        dmxData[currentChannel] = incomingByte;

        // Print value ONLY if it changes
        static uint8_t lastValues[DMX_CHANNELS + 1] = {0};
        if (dmxData[currentChannel] != lastValues[currentChannel]) {
          Serial.printf("DMX Channel %d: %d\n", currentChannel,
                        dmxData[currentChannel]);
          lastValues[currentChannel] = dmxData[currentChannel];

          // Only update display every 200ms
          if (millis() - lastDisplayUpdate > displayInterval) {
            updateDisplay(currentChannel, dmxData[currentChannel]);
            lastDisplayUpdate = millis(); // Update the timer
          }
        }
        currentChannel++;
      }
    }

    lastByteTime = now;
  }
}

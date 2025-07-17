/*
  Pins:
  RS485 (DMX): RO --> D0 (RX)
  Encoder: DT (D2), CLK (D3), SW (D5)
  Relay: D4
  Display OLED: SDA (A4), SCL (A5)

  Libraries:
  EncoderButton: https://github.com/Stutchbury/EncoderButton
  DMXSerial: https://github.com/mathertel/DMXSerial
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DMXSerial.h>
#include <EncoderButton.h>
#include <Wire.h>

enum mode { PAGE, DMX };

// pins
#define DT 2
#define CLK 3
#define RELAY_PIN 4
#define CLICK_PIN 5
// display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define Y_CENTER 10
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// pages
#define MAIN_PAGE 0
#define DMX_PAGE 1
#define TEST_PAGE 2

int currentPage = 0;
const int maxPage = 2;
int dmx_value = 0;
int dmxChannel = 1;
int displayMode = PAGE;

bool relayState = LOW;

// testing led
const int ledPin = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Rotary encoder
EncoderButton eb1(DT, CLK, CLICK_PIN);

void setup() {

  // Serial.begin(9600);

  /*
  -----------------------
  the issue is in the following line, by uncommenting the line, the encoder
  resumes working.
  --------------
  */
  DMXSerial.init(DMXReceiver);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  delay(10);
  // Ensure pump is off
  digitalWrite(RELAY_PIN, LOW);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    // Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  eb1.setEncoderHandler(onEb1Moved);

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.clearDisplay();
  display.setCursor(0, Y_CENTER);
  display.print("boot...");
  display.display();

  delay(1000);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  eb1.update();

  if (currentPage > maxPage) {
    currentPage = maxPage;
  } else if (currentPage < 0) {
    currentPage = MAIN_PAGE;
  }

  // pages
  switch (currentPage) {
  case MAIN_PAGE:
    display.clearDisplay();
    display.setCursor(0, Y_CENTER);
    display.print("Ready");
    display.display();
    break;
  case DMX_PAGE:
    display.clearDisplay();
    display.setCursor(0, Y_CENTER);
    if (displayMode == PAGE) {
      display.print("CH: ");
    } else {
      display.print("SET CH: ");
    }
    display.setCursor(90, Y_CENTER);
    display.print(dmxChannel);
    display.display();
    break;
  case TEST_PAGE:
    display.clearDisplay();
    display.setCursor(0, Y_CENTER);
    display.print("Test");
    display.display();
    break;
  default:
    break;
  }

  // DMX channel read

  // unsigned long lastPacket = DMXSerial.noDataSince();

  // if (lastPacket < 5000) {
  //   dmx_value = DMXSerial.read(dmxChannel);
  //   if (dmx_value > 100) {
  //     digitalWrite(RELAY_PIN, HIGH);
  //   } else {
  //     digitalWrite(RELAY_PIN, LOW);
  //   }

  // } else {
  //   //no data was received since 5 seconds or more.
  // }
}

void onEb1Moved(EncoderButton &eb) {
  if (displayMode == PAGE) {
    currentPage += eb.increment();
  }
}

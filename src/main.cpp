#include <Arduino.h>
#include <FastLED.h>
#include <esp_wifi.h>
#include "httpServer.h"
#include "commands.h"

// LED Setup
#define NUM_LEDS      15
#define COLOR_ORDER   GRB
#define BRIGHTNESS    5
#define LED_DATA_OUT  25
#define CHIPSET       WS2812B

// global Vars
CRGB g_LEDs[NUM_LEDS] = {0};
httpServer g_HTTP_SERVER("Byakuya", "03263812083233064562");
int displayMode = enum_commands::noChoice;

// Prototypes
void DisplayLEDs();

void setup() {
  // Recommended sanity delay
  delay(1000);

  // Setup Serial, drop if no connection within the first second. 
  Serial.begin(9600);
  unsigned long lastTimeCheck = millis();
  while(!Serial) {
    delay(5);
    if (millis() - lastTimeCheck > 1000) break;
  }

  // WiFi setup
  g_HTTP_SERVER.initializeAndStart();

  // FastLED setup
  pinMode(LED_DATA_OUT, OUTPUT);
  FastLED.addLeds<CHIPSET, LED_DATA_OUT, COLOR_ORDER>(g_LEDs, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInMilliWatts(4300);
  FastLED.clear(true);
}

void loop() {
  int displayModeBuffer = g_HTTP_SERVER.serve();
  if (displayModeBuffer > enum_commands::noChoice && displayModeBuffer < enum_commands::outOfScope)
    displayMode = displayModeBuffer;

  DisplayLEDs();
  FastLED.show();
  
  delay(100);
}

void DisplayLEDs() {
  static int lastStart = 0;
  static int length = 3;
  
  switch(displayMode) {
    case enum_commands::next:
      for (int i = lastStart; i < lastStart + length; i++) {
        g_LEDs[i % NUM_LEDS] = CRGB::Black;
      }
    
      for (int i = lastStart + length; i < lastStart + 2 * length; i++) {
        g_LEDs[i % NUM_LEDS] = CRGB::Yellow;
      }

      lastStart %= NUM_LEDS;

      break;

    case enum_commands::previous:
      for (int i = lastStart; i < lastStart + length; i++) {
        g_LEDs[i % NUM_LEDS] = CRGB::Black;
      }

      lastStart -= length;
      if (lastStart < 0)
        lastStart = NUM_LEDS - lastStart;
    
      for (int i = lastStart; i < lastStart + length; i++) {
        g_LEDs[i % NUM_LEDS] = CRGB::Yellow;
      }

      lastStart %= NUM_LEDS;

      break;

    case enum_commands::circle:
    default:
      g_LEDs[lastStart] = CRGB::Black;
    
      for (int i = ++lastStart; i < lastStart + length; i++) {
        g_LEDs[i % NUM_LEDS] = CRGB::Yellow;
      }

      lastStart %= NUM_LEDS;

      break;
  }
}
#include <Arduino.h>
#include <FastLED.h>
#include <esp_wifi.h>
#include "httpServer.h"
#include "effects.h"

// LED Setup
#define NUM_LEDS      15
#define COLOR_ORDER   GRB
#define BRIGHTNESS    5
#define LED_DATA_OUT  25
#define CHIPSET       WS2812B

// global Vars
CRGB g_LEDs[NUM_LEDS] = {0};
httpServer g_HTTP_SERVER("Byakuya", "03263812083233064562");

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
  g_HTTP_SERVER.initializeAndStart(NUM_LEDS);

  // FastLED setup
  pinMode(LED_DATA_OUT, OUTPUT);
  FastLED.addLeds<CHIPSET, LED_DATA_OUT, COLOR_ORDER>(g_LEDs, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInMilliWatts(4300);
  FastLED.clear(true);
}

void loop() {
  Effect* effect = g_HTTP_SERVER.serve();

  if(effect == NULL) {
    DisplayLEDs();
  }
  else {
    effect->display_LEDs(g_LEDs);
  }

  FastLED.show();
  
  delay(100);
}

void DisplayLEDs() {
  static int lastStart = 0;
  static int length = 3;
  
  g_LEDs[lastStart] = CRGB::Black;

  for (int i = ++lastStart; i < lastStart + length; i++) {
    g_LEDs[i % NUM_LEDS] = CRGB::Yellow;
  }

  lastStart %= NUM_LEDS;
}
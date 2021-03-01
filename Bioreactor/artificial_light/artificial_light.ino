#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    20

CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}

void loop() {
  allLightsOff();
}

void allLightsOn(){
  for (int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB ( 255, 255, 255);
  }
  FastLED.show();
}

void allLightsOff(){
  for (int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB ( 0, 0, 0);
  }
  FastLED.show();
}

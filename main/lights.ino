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

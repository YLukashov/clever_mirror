#include <FastLED.h> 

#define NUM_LEDS 100 
#define PIN 15                  

CRGB leds[NUM_LEDS];

void setup() {
   Serial.begin(9600);
   FastLED.addLeds <WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
   FastLED.setBrightness(50);
   pinMode(PIN, OUTPUT);
}

void temp_lenta(int t){
  const int min_t = -40;
  const int max_t = 40;
  const int diaposon_hue = 160;
  const int number_size_lenta = 100;
  int coeff = diaposon_hue / (abs(min_t) + abs(max_t));
  int color = 0;
  color += abs(40 - t) * coeff;
  for(int i = 0; i < number_size_lenta; i++){
        leds[i].setHue(color);
  }
  FastLED.show();
}

void loop() {
  for(int i = -40; i <= 40; i++){
    Serial.println(i);
     temp_lenta(i);
  }
}

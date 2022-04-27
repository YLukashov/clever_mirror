#include <LiquidCrystal.h>
#include <FastLED.h> // подключаем библиотеку

#define NUM_LEDS 100 // указываем количество светодиодов на ленте
#define PIN 15                    // указываем пин для подключения ленты

CRGB leds[NUM_LEDS];

constexpr uint8_t PIN_RS = 12;
constexpr uint8_t PIN_EN = 13;
constexpr uint8_t PIN_DB4 = 2;
constexpr uint8_t PIN_DB5 = 0;
constexpr uint8_t PIN_DB6 = 4;
constexpr uint8_t PIN_DB7 = 5;

int count_touching = 0;
const int count_names = 3;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

void temp_lenta(int t) {
  const int min_t = -40;
  const int max_t = 40;
  const int diaposon_hue = 160;
  const int number_size_lenta = 100;
  int coeff = diaposon_hue / (abs(min_t) + abs(max_t));
  int color = 0;
  color += abs(40 - t) * coeff;
  //Serial.println(color);
  for (int i = 0; i < number_size_lenta; i++) {
    leds[i].setHue(color);
  }
  FastLED.show();
  delay(50);
}

void print_lcd_display(int value) {
  char *names[count_names] = {"Temperature:", "Wind_speed:", "Direction_of_the_wind:"};
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print(names[count_touching]);
  lcd.setCursor(2, 1);
  lcd.print(value);
}

void dop(int value) {
  if(count_touching == 0){
     temp_lenta(value);
    }
  print_lcd_display(value);
  
}

void setup() {
  int val = 100;
  print_lcd_display(100);

  Serial.begin(9600);
  FastLED.addLeds <WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(50);
  pinMode(PIN, OUTPUT);
}

void loop() {
//  for (int i = -40; i <= 40; i++) {
//    Serial.println(i);
//    temp_lenta(i);
//  }
    if(count_touching == 0){
      Serial.println("Введите температуру: ");
    }
    if(count_touching == 1){
      Serial.println("Введите скорость ветра: ");
    }
    if(count_touching == 2){
      Serial.println("Введите направление ветра: ");
    }
    int v = 0; 
    if (Serial.available() > 0) {
       int v = Serial.read();
       Serial.println(v);
       dop(v);
    }
    delay(2000);
}

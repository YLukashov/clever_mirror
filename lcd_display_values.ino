    #include <LiquidCrystal.h>
     
    constexpr uint8_t PIN_RS = 6;
    constexpr uint8_t PIN_EN = 7;
    constexpr uint8_t PIN_DB4 = 8;
    constexpr uint8_t PIN_DB5 = 9;
    constexpr uint8_t PIN_DB6 = 10;
    constexpr uint8_t PIN_DB7 = 11;

    int count_touching = 0;
    const int count_names = 3;
     
    LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

    void print_lcd_display(int value){
      char *names[count_names] = {"Temperature:", "Wind_speed:", "Direction_of_the_wind:"};
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print(names[count_touching]);
      lcd.setCursor(0, 1);
      lcd.print(value);
    }
     
    void setup() {
      int val = 100;
      print_lcd_display(val);
    }
     
    void loop() {
      
    }

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IN1 2
bool state = 0;


void setup() {
    lcd.init();
    lcd.backlight();
    pinMode(IN1, OUTPUT);

}


void loop() {
    lcd.print("Hello World");
    state = !state;
    digitalWrite(IN1, state);
}
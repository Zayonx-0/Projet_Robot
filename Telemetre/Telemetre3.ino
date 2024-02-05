#define echoPinG 12
#define trigPinG 11

#define echoPinD A3
#define trigPinD A0

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
int distance;
bool state = 0;

void setup() {
  pinMode(trigPinG, OUTPUT);
  pinMode(echoPinG, INPUT);
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Distance D:");
  lcd.setCursor(0,1);
  lcd.print("Distance G:");
  Serial.begin(9600);
}

void loop() {
  static unsigned short DistanceD, DistanceG, lastD, lastG, durationG, durationD;
  digitalWrite(trigPinG, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinG, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinG, LOW);

  durationG = pulseIn(echoPinG, HIGH, 5883);

  digitalWrite(trigPinD, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinD, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinD, LOW);


  durationD = pulseIn(echoPinD, HIGH, 5883);
  
  DistanceG = durationG * 0.034 / 2;
  DistanceD = durationD * 0.034 / 2;
  
  if (lastD != DistanceD) {
    lastD = DistanceD;
    lcd.setCursor(11, 0);
    if (DistanceD < 10) {
      lcd.print((String)DistanceD + ' ');
    } else {
    lcd.print(DistanceD);
    }
  }
  
  if (lastG != DistanceG) {
    lastG = DistanceG;
    lcd.setCursor(11, 1);
    if (DistanceG < 10) {
      lcd.print((String) DistanceG + ' ');
    } else {
      lcd.print(DistanceG);
    }
  }
}
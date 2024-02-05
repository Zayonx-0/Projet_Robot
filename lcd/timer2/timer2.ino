#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Addressage de notre écran LCD à l'addresse 0x27
                                    // en définissant les dimensions (16 colonnes, 2 lignes)
void setup()
{
  lcd.init();                       // Initialisation de l'écran LCD
  lcd.backlight();                  // Allumage de l'éclairage de l'écran.
  lcd.setCursor(5, 0);              // Positionnement du curseur à la 6èle colonne à la 1ère ligne
  lcd.print("TEMPS:");              // Affichage du message "TEMPS" sur l'écran LCD
  lcd.setCursor(0, 1);
  lcd.print("M:");
  lcd.setCursor(4, 1);
  lcd.print("S:");
  lcd.setCursor(9, 1);
  lcd.print("D:");
}

void loop()
{
  unsigned long int t = millis();
  static unsigned long int t0;
  static unsigned int D, S, M;
  if (t - t0 > 100) {
    t0 = t;
    D++;
    if (D == 10) {
      D = 0;
      S++;
      if (S == 60) { 
        S = 0;
        M++;
        lcd.setCursor(2, 1);
        lcd.print(M);
      }
      lcd.setCursor(6, 1);
      if (S < 10) {
        lcd.print(" ");
      }
      lcd.print(S);
    }
    lcd.setCursor(11, 1);
    lcd.print(D);
  }
}

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // Addressage de notre écran LCD à l'addresse 0x27
                                  // en définissant les dimensions (16 colonnes, 2 lignes)

void setup()
{
  lcd.init();                 // Initialisation de l'écran LCD
  lcd.backlight();            // Allumage de l'éclairage de l'écran.
  lcd.setCursor(2,1);         // Positionnement du curseur (3ème caractère; 2ème ligne)
  lcd.print("Hello World");   // Affichage de notre message à la position actuelle du curseur
}

void loop()
{
}

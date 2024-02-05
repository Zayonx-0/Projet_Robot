#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);   // Addressage de notre écran LCD à l'addresse 0x27
                                    // en définissant les dimensions (16 colonnes, 2 lignes)

void setup()
{
  lcd.init();                       // Initialisation de l'écran LCD
  lcd.backlight();                  // Allumage de l'éclairage de l'écran.
  lcd.setCursor(5,0);               // Positionnement du curseur à la 6èle colonne à la 1ère ligne
  lcd.print("TEMPS:");              // Affichage du message "TEMPS" sur l'écran LCD
  lcd.setCursor(0,1);               // Positionnement du curseur à la 1ère colonne à la 2ème ligne
  lcd.print("Secondes:");           // Affichage du message "Secondes:" sur l'écran LCD
}

void loop()
{
    lcd.setCursor(9,1);             // positionnement du curseur à la 10ème colonnes à la 2 ème ligne. 
    lcd.print(millis() / 1000);     // Affichage du nombre de secondes écoulées
                                    // depuis le démarrage du programme. 
    delay(1000);                    // Attente de 1 seconde entre chaque rafraichissement
}

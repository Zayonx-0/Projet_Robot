#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Addressage de notre écran LCD à l'addresse 0x27

#define VOIE1 8
#define VOIE2 9
#define VOIE3 10

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("V1:");
    lcd.setCursor(5,0);
    lcd.print("V2:");
    lcd.setCursor(10,0);
    lcd.print("V3:");
    pinMode(VOIE1, INPUT);
    pinMode(VOIE2, INPUT);
    pinMode(VOIE3, INPUT);

}
void loop() {
    static unsigned long int t0;
    if (millis() - t0 > 300) {
        unsigned long voie1 = pulseIn(VOIE1, HIGH);         // La fonction pulseIn renvoie le temps haut
        unsigned long voie2 = pulseIn(VOIE2, HIGH);         // d'un signal si en 2ème paramètre se trouve
        unsigned long voie3 = pulseIn(VOIE3, HIGH);         // "HIGH". En premier paramètre on entre
        t0 = millis();                                      // le pin associé à notre signal. 
        lcd.setCursor(0,1);                                 // Placement du curseur sur la 2ème ligne
        lcd.print((String)voie1 + "  " + voie2 + "  " + voie3 + " "); // Affichage de nos 3 valeurs sur toute la ligne. 
    }
}
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Addressage de notre écran LCD à l'addresse 0x27
#define VOIE1 8
#define VOIE2 9
#define VOIE3 10

#define In1 2
#define In2 3
#define In3 4
#define In4 7
#define EnA 5
#define EnB 6

#define DROIT 1
#define GAUCHE 0
#define STOP 0
#define AVANCE 1
#define RECUL 0


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
        unsigned long voie1 = pulseIn(VOIE1, HIGH);
        unsigned long voie2 = pulseIn(VOIE2, HIGH);
        unsigned long voie3 = pulseIn(VOIE3, HIGH);
    if (millis() - t0 > 300) {
        t0 = millis();                                      // le pin associé à notre signal. 
        lcd.setCursor(0,1);                                 // Placement du curseur sur la 2ème ligne
        lcd.print((String)voie1 + "  " + voie2 + "  " + voie3 + " "); // Affichage de nos 3 valeurs sur toute la ligne. 
    }
    if (voie2 > 1540) {
        cmd_motor(0, 1, voie2 * 255 / 2000)
    }
}




void cmd_motor(bool motor, bool direction = 0, short power = 0) {
    float kfactor = 1.1495;
    if (motor) { // Moteur droit
        power = (power * 2.55) * kfactor;
        if (direction) { // marche avant
            digitalWrite(In1, LOW);           // On paramètre le pont en H afin que le moteur droit
            digitalWrite(In2, HIGH);          // soit configuré de manière à avancer. 
            analogWrite(EnB, power);          // On applique une PWM de rapport cyclique définit par la variable power pour le moteur droit.
        } else { // Marche arrière
            digitalWrite(In2, LOW);           // On paramètre le pont en H afin que le moteur droit soit
            digitalWrite(In1, HIGH);          // configuré de manière à reculer. 
            analogWrite(EnB, power);          // On applique une PWM de rapport cyclique définit par la variable power pour le moteur droit.
        }
    } else { // Moteur gauche
        power = (power * 2.55) 
        if (direction) { // Marche avant
            digitalWrite(In3, HIGH);          // On paramètre le pont en H afin que le moteur gauche soit configuré
            digitalWrite(In4, LOW);           // de manière à avancer
            analogWrite(EnA, power);          // On applique une PWM de rapport cyclique définit par la variable power pour le moteur droit.
        } else { // Marche arrière
            digitalWrite(In3, LOW);           // On paramètre le pont en H afijn que le moteur gauche soit configuré
            digitalWrite(In4, HIGH);          // de manière à reculer. 
            analogWrite(EnA, power);          // On applique une PWM de rapport cyclique définit par la variable power pour le moteur gauche.
        }
    }
}
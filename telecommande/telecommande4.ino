#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Addressage de notre écran LCD à l'addresse 0x27

#define VOIE1 8
#define VOIE2 9
#define VOIE3 10

#define echoPinG 12
#define trigPinG 11
#define echoPinD A3
#define trigPinD A0
#define trigPinF 13
#define echoPinF A1

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

#define IrG A2
#define IrD A6

void cmd_motor(bool motor, bool direction = 0, short power = 0);
float movingAverage(float newValue, int tab);

unsigned long int t0 = 0;
const int N = 6;
int readings[N];
int readIndex = 0;

int readings2[N];
int readIndex2 = 0;


float total = 0;
float total2 = 0;
float average = 0;

float total3 = 0;
int readIndex3 = 0;
int readings3[N];


void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    pinMode(VOIE1, INPUT);
    pinMode(VOIE2, INPUT);
    pinMode(VOIE3, INPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    pinMode(trigPinG, OUTPUT);
    pinMode(echoPinG, INPUT);
    pinMode(trigPinD, OUTPUT);
    pinMode(echoPinD, INPUT);
    pinMode(echoPinF, INPUT);
    pinMode(trigPinF, OUTPUT);

}

void loop() {
    static unsigned long int t0;
    static unsigned short DistanceDSon, DistanceGSon, DistanceFSon, lastD, lastG, durationG, durationD, durationF, DistanceD, DistanceG;
    unsigned long voie3 = pulseIn(VOIE3, HIGH);
    if (voie3 < 1500) { // mode Manuel
        unsigned long voie1 = pulseIn(VOIE1, HIGH);
        unsigned long voie2 = pulseIn(VOIE2, HIGH);
        if (!(voie1 < 2050 && voie1 > 950) || !(voie2 < 2050 && voie2 > 950)) {
            cmd_motor(1, 0, 0);
            cmd_motor(0, 0, 0);
            return;
        }
        short RFactor = 100;
        short LFactor = 100;
        short RSpeed = 0;
        short LSpeed = 0;
        short mappedVoie2 = map(voie2, 1000, 2010, -100, 100);
        short mappedVoie1 = map(voie1, 1000, 2010, -100, 100);
        if (mappedVoie1 <= -5) { // Turn right
            LFactor = map((100 - abs(mappedVoie1)), 0, 100, 30, 100);
            RFactor = 100;
        } else if (mappedVoie1 >= 5) { // Turn left
            RFactor = map((100 - abs(mappedVoie1)), 0, 100, 30, 100);
            LFactor = 100;
        } else {
            RFactor = 100;
            LFactor = 100;
        }

        if (mappedVoie2 <= -10 || mappedVoie2 >= 10) {
            RSpeed = (RFactor / 100.0) * mappedVoie2;
            LSpeed = (LFactor / 100.0) * mappedVoie2;
            if (RSpeed > 100) {
                RSpeed = 100;
            } else if (RSpeed > 200) {
                RSpeed = 0;
            }

            if (LSpeed > 100) {
                LSpeed = 100;
            } else if (LSpeed > 200) {
                LSpeed = 0;
            }
        } else {
            RSpeed = 0;
            LSpeed = 0;
        }

        if (RSpeed >=0) {
            cmd_motor(1, 1, RSpeed);
        } else {
            cmd_motor(1, 0, abs(RSpeed));
        }

        if (LSpeed >= 0) {
            cmd_motor(0, 1, LSpeed);
        } else {
            cmd_motor(0, 0, abs(LSpeed));
        }

        if (millis() - t0 > 300) {
            t0 = millis();
            lcd.setCursor(0,0);
            lcd.print((String)voie1 + "  " + voie2 + "  " + voie3 + " ");
            lcd.setCursor(0,1);
            lcd.print((String)LSpeed + "  " + RSpeed + "           ");
        }
    } else {
        digitalWrite(trigPinF, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPinF, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinF, LOW);

        durationF = pulseIn(echoPinF, HIGH, 5883);

        DistanceFSon = durationF * 0.034 / 2;

        DistanceD = (pow(analogRead(IrD), - 1.25) * 49570);
        DistanceG = (pow(analogRead(IrG), - 1.25) * 49570);

        if (DistanceD >= 80) DistanceD = 70;
        if (DistanceG >= 80) DistanceG = 70;


        static unsigned short AverageG = 0;
        static unsigned short AverageD = 0;
        static unsigned short AverageF = 0;

    DistanceD = map(DistanceD, 0, 70, 20, 35);
    DistanceG = map(DistanceG, 0, 70, 20, 35);


    if (DistanceD > DistanceG) {
        DistanceD = floor(DistanceD * 1.20);
        cmd_motor(1, 1, DistanceG);
        cmd_motor(0, 1, DistanceD);

    } else if (DistanceD < DistanceG) {
        DistanceG = floor(DistanceG * 1.20);
        cmd_motor(1, 1, DistanceG);
        cmd_motor(0, 1, DistanceD);

    } else {
        cmd_motor(1, 1, 30);
        cmd_motor(0, 1, 30);
    }
}}


void cmd_motor(bool motor, bool direction = 0, short power = 0) {
    float kfactor = 1;
    if (motor) { // Moteur droit
        if (power == 0) {
            analogWrite(EnB, 0);
        }
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
        if (power == 0) {
            analogWrite(EnA, 0);
        }
        power = (power * 2.55); 
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



/*float movingAverage(float newValue, int tab) {
    if (tab == 1) {
    total = total - readings[readIndex];
    readings[readIndex] = newValue;
    total = total + readings[readIndex];
    readIndex = readIndex + 1;
    if (readIndex >= N) {
        readIndex = 0;
    }
    average = total / N;
    return average;
    } else if (tab == 2) {
    total2 = total2 - readings2[readIndex2];
    readings2[readIndex2] = newValue;
    total2 = total2 + readings2[readIndex2];
    readIndex2 = readIndex2 + 1;
    if (readIndex2 >= N) {
        readIndex2 = 0;
    }
    average = total2 / N;
    return average;
    } else {
        total3 = total3 - readings3[readIndex3];
        readings3[readIndex3] = newValue;
        total3 = total3 + readings3[readIndex3];
        readIndex3 = readIndex3 + 1;
        if (readIndex3 >= N) {
            readIndex3 = 0;
        }
        average = total3 / N;
        return average;
    }
}*/
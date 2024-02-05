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

static unsigned long int t0;

void cmd_motor(bool motor, bool direction, short power);

void setup() {
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    Serial.begin(9600);

}

void loop() {
    static bool seDeplace = 0;
    if (millis() - t0 > 1000) {
        t0 = millis();
        if (seDeplace) {
        cmd_motor(DROIT, AVANCE, 40);
        cmd_motor(GAUCHE, AVANCE, 38);
        } else {
            cmd_motor(DROIT, AVANCE, STOP);
            cmd_motor(GAUCHE, AVANCE, STOP);
        }
        seDeplace = !seDeplace;
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
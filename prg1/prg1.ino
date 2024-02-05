#define In1 2
#define In2 3
#define In3 4
#define In4 7
#define EnA 5 // Moteur droit
#define EnB 6 // Moteur gauche

unsigned long int t0;     // Variable de temps afin de rempalcer le delay de manière non blocant. 

void setup() {
    pinMode(In1, OUTPUT); // Tous les transistors de notre pont en H
    pinMode(In2, OUTPUT); // sont des transistors de sorties. 
    pinMode(In3, OUTPUT); // Ont les définit donc comme tel dans notre programme; 
    pinMode(In4, OUTPUT);
    pinMode(EnA, OUTPUT); // EnA et EnB sont nos pins générant notre PWM
    pinMode(EnB, OUTPUT); // afin de faire varier la vitesse des moteurs. 

    digitalWrite(In2, LOW);  
    digitalWrite(In1, HIGH); // Ont met les transistors 1 et 4 comme étant passant
    digitalWrite(In3, LOW);  // ce qui a pour effet de sélectionner le sens de rotation
    digitalWrite(In4, HIGH); // des deux moteurs en marche avant. 
}

void loop() {
    static int counter = 0;                 // Compteur du nombre de boucles effectués. 
    if (millis() - t0 > 1000) {             // Toutes les secondes, on rentre dans la boucle
      t0 = millis();                        // afin de mettre en marche ou non les moteurs. 
        if (counter == 1 || counter == 3) { // Lors de la deuxième entrée dans la 1ère boucle 
            analogWrite(EnA, 255);          // et de la 4ème, on met en marche les moteurs
            analogWrite(EnB, 255);
        } else {                            // Sinon, on met les rapports cycliques à 0 (Arrêt des moteurs)
            analogWrite(EnA, 0);
            analogWrite(EnB, 0);
        }
        counter++;                          // On incrémente notre compteur. 
      
    }
}

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
}

void loop() {
    static bool seDeplace = 0;                    // Booléen indiquant si oui ou non on restera à l'arrêt lors du passage dans la boucle.
    static bool sens = 0;                      // Booléen indiquant si le robot doit avancer ou reculer lors du passage dans la boucle. 
    static int counter = 0;                    // Compteur du nombre de séquences effectués. 
    if (millis() - t0 > 1000 && counter <=4) { // Ici, la fonction millis() - t0 nous permet d'avoir notre delay non bloquant de 1s. 
                                               // On vérifie aussi par la même occasion le nombre de séquences effectués (On doit en faire 4)
      t0 = millis();                           // Reset du compteur de millisecondes permettant notre delay non bloquant. 
        if (seDeplace) {                          // Si le booléen est à 1, alors on doit se déplacer. 
            analogWrite(EnA, 255);             // Paramétrage de la vitesse du moteur droit à 100%.
            analogWrite(EnB, 255);             // Paramétrage de la vitesse du moteur gauche à 100%.
        } else {
            analogWrite(EnA, LOW);             // Sinon, si seDeplace est à 0 celà signifie que l'on doit s'arrêter lors de cette séquence. 
            analogWrite(EnB, LOW);
            counter++;                         // On incrémente notre compeur signifiant que l'on a effectué une séquence. 
        }
        if (sens && seDeplace) {                  // Si seDeplace est à 1 alors on doit faire bouger le robot, et si sens est à 1
            digitalWrite(In2, LOW);            // on déplace le robot en marche avant. 
            digitalWrite(In1, HIGH);           // On paramètre le pont en H afin que les deux moteurs soient 
            digitalWrite(In3, LOW);            // configurés de manière à avancer. 
            digitalWrite(In4, HIGH);
            sens = !sens;                      // On inverse le sens de déplacement du robot pour la prochaine boucle.
        } else if (seDeplace) {                   // Sinon si seDeplace est à 1 mais que sens est à 0, alors le robot doit reculer. 
            digitalWrite(In2, HIGH);           // On paramètre donc le pont en H afin que les deux moteurs soient 
            digitalWrite(In1, LOW);            // configurés de manière à reculer. 
            digitalWrite(In3, HIGH);     
            digitalWrite(In4, LOW);
            sens = !sens;                      // On inverse le sens du déplacement du robot pour la prochaine boucle
        }
        seDeplace = !seDeplace;                      // On inverse le booléen seDeplace. Celà signifie que si lors du passage dans la boucle
                                               // le robot s'est déplacé, alors dans le prochain passage de boucle le robot sera dans
                                               // sa phase d'arrêt de 1seconde. 
    }
}
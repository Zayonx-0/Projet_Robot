#define In1 2
#define In2 3
#define In3 4
#define In4 7
#define EnA 5
#define EnB 6

#define IrG A2
#define IrD A6
#define IrF A7

void cmd_motor(bool motor, bool direction = 0, short power = 0);


void setup() {
    Serial.begin(9600);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    pinMode(IrD, INPUT);
    pinMode(IRG, INPUT);
    lcd.init();
    lcd.backlight();
    analogReference(EXTERNAL);

}

void loop() {
    static unsigned long int t0, t1, inLoopTimer
    static unsigned short DistanceG, DistanceD, DistanceF;
    if (millis() - t0 > 25) {
        t0 = millis();
        if (t0 > 60 * 1000) return;
        DistanceD = (pow(analogRead(IrD), - 1.25) * 49570);
        DistanceG = (pow(analogRead(IrG), - 1.25) * 49570);
        DistanceF = (pow(analogRead(IrF), - 1.25) * 49570);

        if (DistanceD >= 80) DistanceD = 70;
        if (DistanceG >= 80) DistanceG = 70;
        if (DistanceF >= 80) DistanceF = 70;

        if (DistanceF < 15 || DistanceD < 15 || DistanceG < 15) {
            inLoopTimer = millis();

            while (DistanceF < 20 || DistanceD < 20 || DistanceG < 20) {
                if (millis() - t1 > 10) {
                    t1 = millis();

                    if (millis() - inLoopTimer > 2000 || inLoop > 400) {
                        inLoopTimer = millis();
                        inLoop = 0;
                        cmd_motor(1, 0, 80);
                        cmd_motor(0, 0, 80);
                        delay(100);
                        cmd_motor(1, 1, 0);
                        cmd_motor(0, 1, 0);
                        return;
                    }

                    if (DistanceD > DistanceG) {
                        cmd_motor(1, 0, 35);
                        cmd_motor(0, 0, 25);
                    }
                    else {
                        cmd_motor(1, 0, 25);
                        cmd_motor(0, 0, 35);
                    }

                    DistanceD = (pow(analogRead(IrD), -1.25) * 49570);
                    DistanceG = (pow(analogRead(IrG), -1.25) * 49570);
                    DistanceF = (pow(analogRead(IrF), -1.25) * 49570);

                    if (DistanceD >= 80) DistanceD = 70;
                    if (DistanceG >= 80) DistanceG = 70;
                    if (DistanceF >= 80) DistanceF = 70;
                }
                return;
            }
        }
    }
}

void cmd_motor(bool motor, bool direction = 0, short power = 0) {
    float kfactor = 1;
    if (motor) {
        if (power == 0) {
            analogWrite(EnB, 0);
        }
        power = (power * 2.55) * kfactor;
        if (direction) {
            digitalWrite(In1, LOW);   
            digitalWrite(In2, HIGH);  
        } else {
            digitalWrite(In2, LOW);   
            digitalWrite(In1, HIGH);  
        }
        analogWrite(EnB, power);
    } else {
        if (power == 0) {
            analogWrite(EnA, 0);
        }
        power = (power * 2.55); 
        if (direction) {
            digitalWrite(In3, HIGH); 
            digitalWrite(In4, LOW);  
        } else { // Marche arrière
            digitalWrite(In3, LOW);  
            digitalWrite(In4, HIGH); 
        }
        analogWrite(EnA, power); 
    }
}
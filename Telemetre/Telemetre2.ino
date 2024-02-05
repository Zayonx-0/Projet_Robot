#define echoPin1 12
#define trigPin1 11

unsigned long int t, t0;

void setup() {
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    Serial.begin(9600);
}
void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 5882);
    distance = duration * 0.034 / 2;
    Serial.println((String)"Distance: " + distance + " cm");
}


float Distance(echoPin, trigPin) {

}
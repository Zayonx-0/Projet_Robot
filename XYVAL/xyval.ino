/*****************************************************************

  Affichage dans le moniteur série de la valeur maximale et de
  la valeur minimale des 3 composantes orthogonales
  du champ magnétique, tel que mesurées par le capteur HMC5883L.

  Utile pour calibrer le capteur.

  Basé sur l'exemple publié par Sparkfun:
  https://www.sparkfun.com/tutorials/301
  
  Plus d'infos:
  https://electroniqueamateur.blogspot.com/2019/06/fabrication-dune-boussole-avec-le.html

******************************************************************/

#include <Wire.h> // Bibliothèque pour i2c

#define addresse 0x1E // Adresse i2c du capteur HMC5883

int xmax, xmin, ymax, ymin, zmax, zmin;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Initialisation du HMC5883
  Wire.beginTransmission(addresse);
  Wire.write(0x02);
  Wire.write(0x00); // mode de mesure continue
  Wire.endTransmission();

  // On demande une prise de mesure
  Wire.beginTransmission(addresse);
  Wire.write(0x03);
  Wire.endTransmission();

  // Première lecture
  Wire.requestFrom(addresse, 6);
  if (6 <= Wire.available()) {
    xmin = Wire.read() << 8; //X msb
    xmin |= Wire.read(); //X lsb
    zmin = Wire.read() << 8; //Z msb
    zmin |= Wire.read(); //Z lsb
    ymin = Wire.read() << 8; //Y msb
    ymin |= Wire.read(); //Y lsb
  }

  xmax = xmin;
  ymax = ymin;
  zmax = zmin;
}

void loop() {

  int xbrut, ybrut, zbrut;

  // On demande une prise de mesure
  Wire.beginTransmission(addresse);
  Wire.write(0x03);
  Wire.endTransmission();

  // Lecture des mesures
  Wire.requestFrom(addresse, 6);
  if (6 <= Wire.available()) {
    xbrut = Wire.read() << 8; //X msb
    xbrut |= Wire.read(); //X lsb
    zbrut = Wire.read() << 8; //Z msb
    zbrut |= Wire.read(); //Z lsb
    ybrut = Wire.read() << 8; //Y msb
    ybrut |= Wire.read(); //Y lsb
  }

  Serial.print(xbrut);
  Serial.print(" ");
  Serial.println(ybrut);


}
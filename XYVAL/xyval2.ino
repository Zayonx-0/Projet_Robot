/**********************************************************
   Boussole constituée d'un Arduino, d'un magnétomètre
   HMC5883 et d'un écran LCD Nokia.
   
   Plus d'infos:
   https://electroniqueamateur.blogspot.com/2019/06/fabrication-dune-boussole-avec-le.html
***********************************************************/

#include <Wire.h>  // i2c pour le capteur HMC5883
#define adresse 0x1E // Adresse i2c du capteur HMC5883

// valeurs requises pour calibrer nos mesures (spécifique à votre module):
const int xmin = -426;
const int xmax = 682;
const int ymin = -556;
const int ymax = 105;

// Pour pointer vers le nord géographique plutôt que vers
// le nord magnétique, on additionne la déclinaison, qui dépend
// de l'endroit où vous êtes:
// http://www.magnetic-declination.com/

float declinaison = 0.04;  // en radians

// D/C broche 5,CSE ou CS broche 4, RST broche 3

void setup(void)
{
  // initialiation du capteur HMC5883
  Wire.begin();
  Wire.beginTransmission(adresse);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
  Serial.begin(9600);
}

void loop(void)
{

  int xbrut, ybrut, zbrut, xcalibree, ycalibree;

  // On demande les informations au capteur HMC5883
  Wire.beginTransmission(adresse);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();

  //Lecture des composantes du champ magnétique
  Wire.requestFrom(adresse, 6);
  if (6 <= Wire.available()) {
    xbrut = Wire.read() << 8; //X msb
    xbrut |= Wire.read(); //X lsb
    zbrut = Wire.read() << 8; //Z msb
    zbrut |= Wire.read(); //Z lsb
    ybrut = Wire.read() << 8; //Y msb
    ybrut |= Wire.read(); //Y lsb
  }

  // valeurs calibrées:
  xcalibree = map(xbrut, xmin, xmax, -1000, 1000);
  ycalibree = map(ybrut, ymin, ymax, -1000, 1000);

  // Calcul de l'angle entre le nord magnétique et l'axe x du capteur
  float orientationNord = atan2(ycalibree, xcalibree);

  orientationNord += declinaison;

  // on dessine la flèche à l'angle approprié sur l'afficheur LCD
  Serial.println(orientationNord);

  delay(50);
}
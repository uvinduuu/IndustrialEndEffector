#include "distance.h"

// // below values should be configured
float dv = 41; // vertical distance between the ToF sensors
float dhu = 76; // horizontal distance between the upper ToF sensors
float dhd = 76; // horizontal distance between the lower ToF sensors

// // below values are read and calculated
float relativeDistance;
float dlu; // left upper ToF sensor distance
float dru; // right upper ToF sensor distance
float dld; // left down ToF sensor distance
float drd; // right down ToF sensor distance
float thetaP; // pitch angle (angle around the horizontal axis)
float thetaY; // yaw angle (angle around the vertical axis)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setID();
}

void loop() {
  // put your main code here, to run repeatedly:

  dlu = sensor_1() - 5;
  dru = sensor_2();
  dld = sensor_3();
  drd = sensor_4() - 4;

  relativeDistance = (dlu + dru + dld + drd)/4;

  thetaP = 0.5*atan((dlu-dld)/dv) + 0.5*atan((dru-drd)/dv);
  thetaY = 0.5*atan((dru-dlu)/dhu) + 0.5*atan((drd-dld)/dhd);

  thetaP = degrees(thetaP);
  thetaY = degrees(thetaY);

  Serial.print("Pelative Distance : " + String(relativeDistance) + " ");
  Serial.print("Pitch Angle : " + String(thetaP) + " ");
  Serial.println("Yaw Angle : " + String(thetaY) + " ");

  delay(20);
  
}

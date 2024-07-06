#include <avr/io.h>
#include "delay.h"
#include "uart.h"
#include "TWI.h"
#include "ToF.h"
#include "multi_distance.h"

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

int main(){
  init_uart(); // Intializing the Serial communication with UART protocol
  i2c_init(); // Intializing TWI 
  setID(); // Intializing the multiplexer and the ToF sensors

  while(1){
    for (int i=0;i<5;i++){ // Implementation of the moving average filter
      dlu += sensor_1() - 5;
      dru += sensor_2();
      dld += sensor_3();
      drd += sensor_4() - 4;
      delay_ms(10);
    }

    dlu = dlu/5;
    dru = dru/5;
    dld = dld/5;
    drd = drd/5;

    relativeDistance = (dlu + dru + dld + drd)/4;

    thetaP = 0.5*atan((dlu-dld)/dv) + 0.5*atan((dru-drd)/dv); // Calculating the Pitch
    thetaY = 0.5*atan((dru-dlu)/dhu) + 0.5*atan((drd-dld)/dhd); // Calculating the Yaw

    thetaP = degrees(thetaP);
    thetaY = degrees(thetaY);

    trans_string("Relative Distance : ");
    trans_num(relativeDistance); 
    trans_string(" Pitch Angle : ");
    trans_num(thetaP);
    trans_string(" Yaw Angle : ");
    trans_num(thetaY);
    trans_string("\n");   

    delay_ms(20);
  }
  return 0;
}
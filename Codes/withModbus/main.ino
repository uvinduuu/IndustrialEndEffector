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
  init_rs485(); // Initialize RS485 pins

  while(1){
    dlu = 0;
    dru = 0;
    dld = 0;
    drd = 0;

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

    // Write angles as floats to Modbus registers
    modbus_write_float_registers(MODBUS_SLAVE_ID, 0x0000, thetaP); // Write thetaP as float to registers 0 and 1
    delay_ms(100);
    modbus_write_float_registers(MODBUS_SLAVE_ID, 0x0002, thetaY); // Write thetaY as float to registers 2 and 3

    delay_ms(1000); 
  }
  
  return 0;
}
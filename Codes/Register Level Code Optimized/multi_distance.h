#ifndef MULTI
#define MULTI

#include <avr/io.h>
#include "TWI.h"
#include "ToF.h"

void TCA9548A(uint8_t bus);
void setID();
float sensor_1();
float sensor_2();
float sensor_3();
float sensor_4();

#endif
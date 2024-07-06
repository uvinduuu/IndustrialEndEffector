#ifndef ToF
#define ToF

#include <avr/io.h>
#include "TWI.h"

void vl53l1x_init();
void vl53l1x_measure_distance();
uint16_t vl53l1x_read_distance();

#endif
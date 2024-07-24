#ifndef TWI
#define TWI

#include <avr/io.h>

void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_write(uint8_t data);
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();

#endif
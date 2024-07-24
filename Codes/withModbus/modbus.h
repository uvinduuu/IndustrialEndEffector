#ifndef MODBUS
#define MODBUS

#include <stdint.h> 
#include <avr/io.h>
#include "uart.h"

// Define Modbus Slave ID
#define MODBUS_SLAVE_ID 1

// Define RS485 pins
#define MAX485_DE      PB0
#define MAX485_RE_NEG  PB1

// Function declarations
void init_rs485();
void enable_transmit();
void enable_receive();
void modbus_write_float_registers(uint8_t id, uint16_t address, float value);
void modbus_write_single_register(uint8_t id, uint16_t address, uint16_t value);

// Function to calculate CRC for Modbus
uint16_t calculate_crc(uint8_t *buffer, uint8_t length);

#endif 

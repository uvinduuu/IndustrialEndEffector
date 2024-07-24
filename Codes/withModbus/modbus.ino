// Define Modbus Slave ID
#define MODBUS_SLAVE_ID 1

// Define RS485 pins
#define MAX485_DE      PB0
#define MAX485_RE_NEG  PB1

// Initialize RS485 pins
void init_rs485() {
  DDRB |= (1 << MAX485_DE) | (1 << MAX485_RE_NEG);
  PORTB &= ~(1 << MAX485_DE);
  PORTB &= ~(1 << MAX485_RE_NEG);
}

// Enable RS485 transmit mode
void enable_transmit() {
  PORTB |= (1 << MAX485_DE);
  PORTB |= (1 << MAX485_RE_NEG);
}

// Enable RS485 receive mode
void enable_receive() {
  PORTB &= ~(1 << MAX485_DE);
  PORTB &= ~(1 << MAX485_RE_NEG);
}


// Function to calculate CRC for Modbus
uint16_t calculate_crc(uint8_t *buffer, uint8_t length) {
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < length; pos++) {
    crc ^= (uint16_t)buffer[pos];
    for (int i = 8; i != 0; i--) {
      if ((crc & 0x0001) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

// Function to write two consecutive registers with a float value
void modbus_write_float_registers(uint8_t id, uint16_t address, float value) {
  union {
    float f;
    uint16_t parts[2];
  } float_converter;
  
  float_converter.f = value;

  // Send high part
  modbus_write_single_register(id, address, float_converter.parts[1]);
  delay_ms(100);

  // Send low part
  modbus_write_single_register(id, address + 1, float_converter.parts[0]);
  delay_ms(100);
}

// Function to write a single register on Modbus
void modbus_write_single_register(uint8_t id, uint16_t address, uint16_t value) {
  uint8_t frame[8];
  uint16_t crc;

  frame[0] = id; // Slave ID from the robot controller
  frame[1] = 0x06; // Function code (Write Single Register)
  frame[2] = (address >> 8) & 0xFF; // Address high byte
  frame[3] = address & 0xFF; // Address low byte
  frame[4] = (value >> 8) & 0xFF; // Value high byte
  frame[5] = value & 0xFF; // Value low byte

  crc = calculate_crc(frame, 6);
  frame[6] = crc & 0xFF; // CRC low byte
  frame[7] = (crc >> 8) & 0xFF; // CRC high byte

  enable_transmit();
  for (int i = 0; i < 8; i++) {
    UART_Txchar(frame[i]); // Transmit each byte of the frame over UART
  }
  enable_receive();
}

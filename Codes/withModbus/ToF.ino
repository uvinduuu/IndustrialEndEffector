#define VL53L1X_ADDR 0x52 // Defining the ToF Address

void vl53l1x_init() {
    // Initializing the ToF
    i2c_start();
    i2c_write(VL53L1X_ADDR); // Device address
    i2c_write(0x00); // Default register address
    i2c_write(0x01); 
    i2c_stop();

}

void vl53l1x_measure_distance(){
  i2c_start();
  i2c_write(VL53L1X_ADDR); // Device address
  i2c_write(0x00); 
  i2c_write(0x02); // Setting the measuring mode
  i2c_stop();
}

uint16_t vl53l1x_read_distance() {
    uint16_t distance;
    
    // Read distance high byte
    i2c_start();
    i2c_write(VL53L1X_ADDR); // Device address
    i2c_write(0x14 + 10); // Register address for distance high byte
    i2c_start(); // Repeated start
    i2c_write(VL53L1X_ADDR | 0x01); // Read mode
    uint8_t high_byte = i2c_read_ack();
    
    // Read distance low byte
    uint8_t low_byte = i2c_read_nack();
    i2c_stop();
    
    distance = (high_byte << 8) | low_byte;
    // distance = low_byte;

    return distance;
}




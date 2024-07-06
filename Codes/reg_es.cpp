#include <Arduino.h>
#include <avr/io.h>

#define VL53L1X_ADDR 0x52

void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms; i++) {
        // Configure Timer1
        TCCR1A = 0;  // Clear Timer1 Control Register A
        TCCR1B = 0;  // Clear Timer1 Control Register B
        TCNT1 = 0;   // Clear Timer1 Counter

        // Set Timer1 to CTC mode and set prescaler to 64
        TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

        // Set compare match register for 1ms delay
        OCR1A = 249;

        // Wait for compare match flag to be set
        while (!(TIFR1 & (1 << OCF1A)));

        // Clear compare match flag
        TIFR1 |= (1 << OCF1A);
    }
}

void i2c_init() {
    // Set the clock speed
    TWSR = 0x00;
    TWBR = ((F_CPU/400000)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))));
}

void i2c_start() {
    // Send start condition
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop() {
    // Send stop condition
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void i2c_write(uint8_t data) {
    // Write data to the I2C bus
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}

uint8_t i2c_read_ack() {
    // Read data from the I2C bus with acknowledgment
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

uint8_t i2c_read_nack() {
    // Read data from the I2C bus without acknowledgment
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}



void vl53l1x_init() {
    // Example initialization sequence
    i2c_start();
    i2c_write(VL53L1X_ADDR); // Device address
    i2c_write(0x00); // Register address
    i2c_write(0x01); // Data to write
    i2c_stop();

}

void vl53l1x_measure_distance(){
  i2c_start();
  i2c_write(VL53L1X_ADDR); // Device address
  i2c_write(0x00);
  i2c_write(0x02);
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

int main(){
  Serial.begin(9600);
  i2c_init();
  vl53l1x_init();
  while(1){
    vl53l1x_measure_distance();
    uint16_t distance = vl53l1x_read_distance();
    Serial.print("Distance: ");
    Serial.println(distance);
    delay_ms(100);
  }
  return 0;
}


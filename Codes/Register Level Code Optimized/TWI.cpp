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

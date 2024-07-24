void TCA9548A(uint8_t bus) { // Initializing the multiplexer channel
  i2c_start();
  i2c_write(0x70);
  i2c_write(bus);
  i2c_write(0x01);
  i2c_stop();
}

void setID() { // Initializing the ToF sensors

  TCA9548A(0);
  vl53l1x_init();
 
  TCA9548A(1);
  vl53l1x_init();

  TCA9548A(2);
  vl53l1x_init();

  TCA9548A(3);
  vl53l1x_init();
}

float sensor_1() { // Getting sensor 1 reading
  TCA9548A(0);
  vl53l1x_measure_distance();
  return (float) vl53l1x_read_distance();
}
float sensor_2() { // Getting sensor 2 reading
  TCA9548A(1);
  vl53l1x_measure_distance();
  return (float) vl53l1x_read_distance();
}

float sensor_3() { // Getting sensor 3 reading
  TCA9548A(2);
  vl53l1x_measure_distance();
  return (float) vl53l1x_read_distance();
}

float sensor_4() { // Getting sensor 4 reading
  TCA9548A(3);
  vl53l1x_measure_distance();
  return (float) vl53l1x_read_distance();
}
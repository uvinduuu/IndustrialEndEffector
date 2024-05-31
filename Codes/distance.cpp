#include <Adafruit_VL53L0X.h>
#include <Wire.h>
#include <Arduino.h>

int sensor1, sensor2, sensor3, sensor4;
float sensor_readings[4] = { 0, 0, 0, 0};

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;

/*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
 */

void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setID() {

  // initing LOX1
  TCA9548A(0);
  if (!lox1.begin(0x29)) {
    // Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }

  //initing LOX2
  TCA9548A(1);
  if (!lox2.begin(0x29)) {
    // Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }

  // //initing LOX3
  TCA9548A(2);
  if (!lox3.begin(0x29)) {
    // Serial.println(F("Failed to boot third VL53L0X"));
    while (1)
      ;
  }


  // //initing LOX4
  TCA9548A(3);
  if (!lox4.begin(0x29)) {
    // Serial.println(F("Failed to boot fourth VL53L0X"));
    while (1)
      ;
  }
}

float sensor_1() {
  TCA9548A(0);
  lox1.rangingTest(&measure1, false);
  if (measure1.RangeStatus != 4) {
    sensor1 = measure1.RangeMilliMeter;
  } else {
    sensor1 = 4000;
  }
  return sensor1;
}
float sensor_2() {
  TCA9548A(1);
  lox2.rangingTest(&measure2, false);
  if (measure2.RangeStatus != 4) {
    sensor2 = measure2.RangeMilliMeter;
  } else {
    sensor2 = 4000;
  }
  return sensor2;
}

float sensor_3() {
  TCA9548A(2);
  lox3.rangingTest(&measure3, false);
  if (measure3.RangeStatus != 4) {
    sensor3 = measure3.RangeMilliMeter;
  } else {
    sensor3 = 4000;
  }
  return sensor3;
}

float sensor_4() {
  TCA9548A(3);
  lox4.rangingTest(&measure4, false);
  if (measure4.RangeStatus != 4) {
    sensor4 = measure4.RangeMilliMeter;
  } else {
    sensor4 = 4000;
  }
  return sensor4;
}
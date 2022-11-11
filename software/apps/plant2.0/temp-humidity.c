// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#include <stdbool.h>
#include <stdint.h>

#include "temp-humidity.h"
#include "nrf_delay.h"

#include <math.h>

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void shtc3_init(const nrf_twi_mngr_t* i2c) {
  
  i2c_manager = i2c;

  // Read unique shtc3 ID - should be same every time
  uint8_t whoami = i2c_reg_write(TEMP_MOISTURE_SENSOR, READ_ID);
  printf("WHO AM I? temp-mosture sensor: %x\r\n", whoami);
}
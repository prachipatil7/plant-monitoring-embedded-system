// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>

//#include "lsm303agr.h"
#include "moisture.h"
#include "i2c_utils.h"
#include "nrf_delay.h"
#include <math.h>


// Read the moisture sensor
//
// Return measurement as [What Unit?]
float read_moisture(void) {
  i2c_reg_write(0x28, 0x01, NULL);			       
  return 0.0;
}


void moisture_init(const nrf_twi_mngr_t* i2c) {
  i2c_init(i2c);
}




























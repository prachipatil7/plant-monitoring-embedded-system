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

  i2c_reg_write(MOIST_ADDRESS, MOIST_LED_ON_REG, 0x1);
  //printf("Reading...\n");
	
  //i2c_reg_write(MOIST_ADDRESS, MOIST_POWER_REG, 0x1);
  //printf("Writing 1...\n");
  //nrf_delay_ms(1000);
  
  //uint16_t moisture = (uint16_t) i2c_reg_read(MOIST_ADDRESS,
					       //MOIST_OUT_REG);
  //printf("Read: %d\n", moisture);					       
  //i2c_reg_write(MOIST_ADDRESS, MOIST_POWER_REG, 0x0);
  //printf("Writing 0...\n");
					       
  return 0.0;//(float) moisture;
}


void moisture_init(const nrf_twi_mngr_t* i2c) {
}








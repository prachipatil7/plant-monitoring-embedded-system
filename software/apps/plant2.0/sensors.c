// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>

#include "lsm303agr.h"
#include "sensors.h"
#include "nrf_delay.h"
#include <math.h>

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;


static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr) {
  uint8_t rx_buf = 0;
  nrf_twi_mngr_transfer_t const read_transfer[] = {
     NRF_TWI_MNGR_WRITE(i2c_addr,
			&reg_addr,
			1,
			NRF_TWI_MNGR_NO_STOP),
     NRF_TWI_MNGR_READ(i2c_addr,
		       &rx_buf,
		       1,
		       0)
						   
						   
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

  return rx_buf;
}

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
  //TODO: implement me
  //Note: there should only be a single two-byte transfer to be performed
  uint8_t p_data[] = {reg_addr, data};
  nrf_twi_mngr_transfer_t const write_transfer[] = {
     NRF_TWI_MNGR_WRITE(i2c_addr,
			&p_data,
			2,
			0)				  						   
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
  
}

void lsm_init(const nrf_twi_mngr_t* i2c) {
	return;
}


// Read the moisture sensor
//
// Return measurement as [What Unit?]
float read_moisture(void) {
  printf("Reading...\n");
	
  i2c_reg_write(MOIST_ADDRESS, MOIST_POWER_REG, 0x1);
  printf("Writing 1...\n");
  nrf_delay_ms(1000);
  
  uint16_t moisture = (uint16_t) i2c_reg_read(MOIST_ADDRESS,
					       MOIST_OUT_REG);
  printf("Read: %d\n", moisture);					       
  //i2c_reg_write(MOIST_ADDRESS, MOIST_POWER_REG, 0x0);
  printf("Writing 0...\n");
					       
  return (float) moisture;
}









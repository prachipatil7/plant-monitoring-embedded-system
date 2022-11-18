#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"
#include "i2c_utils.h"
#include <math.h>

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;


uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr) {
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
void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
  uint8_t p_data[] = {reg_addr, data};
  nrf_twi_mngr_transfer_t const write_transfer[] = {
     NRF_TWI_MNGR_WRITE(i2c_addr,
			&p_data,
			1,
			0)				  						   
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
  
}

//Need to check if this is right
void i2c_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;
}


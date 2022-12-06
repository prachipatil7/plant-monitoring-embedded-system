#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"
#include "i2c_utils.h"
#include <math.h>

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

void i2c_change_bit(uint8_t i2c_addr, uint8_t reg_addr, uint8_t bit, uint8_t data) {
  //printf("about 2 read\n");
  uint8_t reg_val = i2c_reg_read(i2c_addr, reg_addr);
  uint8_t new_val;
  if (data == 1) {
     new_val = reg_val | (1 << bit);
  } else {
     new_val = reg_val & ~(1 << bit);
  }
  //printf("about 2 write\n");
  i2c_reg_write(i2c_addr, reg_addr, new_val);
}

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
  //printf("about to read perform\n");
  ret_code_t err = nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);
  //printf("ret code on read is %u\n", err);

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
			2,
			0)				  						   
  };
  //printf("about 2 perform\n");

  ret_code_t err = nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
  if (err != 0){
  printf("ret code on write is %u\n", err);
}
}

void i2c_dev_read(uint8_t i2c_addr, uint8_t* p_data_ptr) {
  nrf_twi_mngr_transfer_t const read_transfer[] = {
            NRF_TWI_MNGR_READ(i2c_addr,
                              p_data_ptr,
                              2,
                              NRF_TWI_MNGR_NO_STOP)};
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 1, NULL);
}


//Need to check if this is right
void i2c_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;
}


#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"
#include "nrf_twi_mngr.h"
#include <math.h>

uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, nrf_twi_mngr_t* i2c_manager);
void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data, nrf_twi_mngr_t* i2c_manager);


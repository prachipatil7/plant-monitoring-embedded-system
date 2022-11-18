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
  // I2C ADDRESS = 0x70
  // READ_ID = 0xEFC8
  uint8_t p_data[] = {0xEF, 0xC8};
  nrf_twi_mngr_transfer_t const write_transfer[] = {
     NRF_TWI_MNGR_WRITE((uint8_t) 0x70,
			&p_data,
			2,
			0)				  						   
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 2, NULL);

  uint8_t whoami = i2c_reg_write((uint8_t) 0x70, (uint8_t) 0x70, uint8_t data);
  printf("WHO AM I? temp-humidity sensor: %x\r\n", whoami);
}
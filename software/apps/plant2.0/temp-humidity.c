// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#include <stdbool.h>
#include <stdint.h>

#include "temp-humidity.h"
#include "nrf_delay.h"

#include <math.h>

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t *i2c_manager = NULL;

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance

void shtc3_init(const nrf_twi_mngr_t *i2c)
{

  i2c_manager = i2c;

  // Read unique shtc3 ID - should be same every time
  // I2C ADDRESS = 0x70
  // READ_ID = 0xEFC8
  uint8_t request[] = {0xEF, 0xC8};
  uint8_t whoami[2];

  nrf_twi_mngr_transfer_t const read_transfer[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &request,
                         2,
                         NRF_TWI_MNGR_NO_STOP),

      NRF_TWI_MNGR_READ((uint8_t)0x70,
                        &whoami,
                        2,
                        0)
  };
  printf("i2c_manager: %x\r\n", i2c_manager);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

  uint16_t upper = (uint16_t) whoami[0];
  upper <<= 8;
  uint16_t lower = (uint16_t) whoami[1];
  uint16_t comb = upper | lower;

  uint16_t mask = 0b0000100000111111;
  uint16_t id = 0b0000100000111111 & comb;

  printf("WHO AM I? temp-humidity sensor: %x\r\n", id);
}

float shtc3_read_temperature(void)
{
  // Read unique shtc3 ID - should be same every time
  // I2C ADDRESS = 0x70
  // WAKEUP = 0x3517
  // READ_T = 0x7866
  uint8_t wakeup[] = {0x35, 0x17};
  uint8_t measurement[] = {0x7C, 0xA2};
  uint8_t temp[2];
  uint8_t sleep[] = {0xB0, 98};

  nrf_twi_mngr_transfer_t const read_transfer1[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &wakeup,
                         2,
                         0)};
  nrf_twi_mngr_transfer_t const read_transfer2[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &measurement,
                         2,
                         0)};
  nrf_twi_mngr_transfer_t const read_transfer3[] = {
      NRF_TWI_MNGR_READ((uint8_t)0x70,
                        &temp,
                        2,
                        NRF_TWI_MNGR_NO_STOP)};
  nrf_twi_mngr_transfer_t const read_transfer4[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &sleep,
                         2,
                         0)
  };

  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer1, 1, NULL);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer2, 1, NULL);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer3, 1, NULL);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer4, 1, NULL);

  uint16_t upper = temp[0];
  upper <<= 8;
  uint16_t comb = upper | temp[1];

  float st = (float) comb;
  float T = st / 65536;
  T *= 175;
  T -= 45;

  printf("TEMP: %f degC\r\n", T);

  return T;
}

float shtc3_read_humidity(void)
{
  // Read unique shtc3 ID - should be same every time
  // I2C ADDRESS = 0x70
  // WAKEUP = 0x3517
  // READ_H = 0x7866
  uint8_t wakeup[] = {0x35, 0x17};
  uint8_t measurement[] = {0x58, 0xE0};
  uint8_t humidity[2];
  uint8_t sleep[] = {0xB0, 98};

  nrf_twi_mngr_transfer_t const read_transfer1[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &wakeup,
                         2,
                         0)};
  nrf_twi_mngr_transfer_t const read_transfer2[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &measurement,
                         2,
                         0)};
  nrf_twi_mngr_transfer_t const read_transfer3[] = {
      NRF_TWI_MNGR_READ((uint8_t)0x70,
                        &humidity,
                        2,
                        NRF_TWI_MNGR_NO_STOP)};
  nrf_twi_mngr_transfer_t const read_transfer4[] = {
      NRF_TWI_MNGR_WRITE((uint8_t)0x70,
                         &sleep,
                         2,
                         0)
  };

  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer1, 1, NULL);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer2, 1, NULL);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer3, 1, NULL);
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer4, 1, NULL);

  uint16_t upper = humidity[0];
  upper <<= 8;
  uint16_t comb = upper | humidity[1];

  float srh = (float) comb;
  float RH = srh / 65536;
  RH *= 100;

  printf("HUMIDITY: %f %\r\n", RH);

  return RH;
}
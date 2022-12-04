// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#include <stdbool.h>
#include <stdint.h>

#include "temp-humidity.h"
#include "nrf_delay.h"
#include "i2c_utils.h"

#include <math.h>

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t *i2c_manager = NULL;

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance

void shtc3_init(const nrf_twi_mngr_t *i2c)
{
  i2c_manager = i2c;
}

float shtc3_read_temperature(void) {
    uint8_t temp[2];

    i2c_reg_write(TEMP_MOISTURE_SENSOR, WAKEUP_REG, WAKEUP_COMM);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, READ_TEMP_REG, READ_TEMP_COMM);
    nrf_twi_mngr_transfer_t const read_transfer[] = {
            NRF_TWI_MNGR_READ(TEMP_MOISTURE_SENSOR,
                              &temp,
                              2,
                              NRF_TWI_MNGR_NO_STOP)};
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 1, NULL);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, SLEEP_REG, SLEEP_COMM);

    uint16_t upper = temp[0];
    upper <<= 8;
    uint16_t comb = upper | temp[1];

    float st = (float) comb;
    float T = st / 65536;
    T *= 175;
    T -= 45;

    //printf("TEMP: %f degC\r\n", T);

    return T;

}

float shtc3_read_humidity(void) {
    uint8_t humidity[2];

    i2c_reg_write(TEMP_MOISTURE_SENSOR, WAKEUP_REG, WAKEUP_COMM);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, READ_HUM_REG, READ_HUM_COMM);
    nrf_twi_mngr_transfer_t const read_transfer[] = {
            NRF_TWI_MNGR_READ(TEMP_MOISTURE_SENSOR,
                              &humidity,
                              2,
                              NRF_TWI_MNGR_NO_STOP)};
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 1, NULL);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, SLEEP_REG, SLEEP_COMM);

    uint16_t upper = humidity[0];
    upper <<= 8;
    uint16_t comb = upper | humidity[1];

    float srh = (float) comb;
    float RH = srh / 65536;
    RH *= 100;

    //printf("HUMIDITY: %f %\r\n", RH);

    return RH;
}
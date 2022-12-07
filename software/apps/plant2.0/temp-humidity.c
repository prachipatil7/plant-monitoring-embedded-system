// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#include <stdbool.h>
#include <stdint.h>

#include "temp-humidity.h"
#include "nrf_delay.h"
#include "i2c_utils.h"

#include <math.h>

void shtc3_init(const nrf_twi_mngr_t *i2c) {
  i2c_init(i2c);
}

float shtc3_read_temperature(void) {
    uint8_t temp[2];

    i2c_reg_write(TEMP_MOISTURE_SENSOR, WAKEUP_REG, WAKEUP_COMM);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, READ_TEMP_REG, READ_TEMP_COMM);
    i2c_dev_read(TEMP_MOISTURE_SENSOR, &temp);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, SLEEP_REG, SLEEP_COMM);

    uint16_t upper = temp[0];
    upper <<= 8;
    uint16_t comb = upper | temp[1];

    float st = (float) comb;
    float T = st / 65536;
    T *= 175;
    T -= 45;

    return T;
}

float shtc3_read_humidity(void) {
    uint8_t humidity[2];

    i2c_reg_write(TEMP_MOISTURE_SENSOR, WAKEUP_REG, WAKEUP_COMM);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, READ_HUM_REG, READ_HUM_COMM);
    i2c_dev_read(TEMP_MOISTURE_SENSOR, &humidity);
    i2c_reg_write(TEMP_MOISTURE_SENSOR, SLEEP_REG, SLEEP_COMM);

    uint16_t upper = humidity[0];
    upper <<= 8;
    uint16_t comb = upper | humidity[1];

    float srh = (float) comb;
    float RH = srh / 65536;
    RH *= 100;

    return RH;
}

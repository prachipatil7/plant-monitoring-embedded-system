// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf



#include "led_driver.h"


// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t *i2c_manager = NULL;

void set_pwm_frequency(uint16_t freq) {
  float prescaleval = ((27000000 / (freq * 4096.0)) + 0.5) - 1;
  uint8_t prescale = (uint8_t)prescaleval;
  printf("%d\n", prescale);
  i2c_change_bit(LED_DEV_ADDR, LED_MODE1_REG, 4, 1);
  i2c_reg_read(LED_DEV_ADDR, LED_PRESCALER_REG);
  i2c_reg_write(LED_DEV_ADDR, LED_PRESCALER_REG, prescale);
  i2c_change_bit(LED_DEV_ADDR, LED_MODE1_REG, 4, 0);
}

void led_on(void) {
    i2c_change_bit(LED_DEV_ADDR, 0x0B, 4, 1);
}

void led_init(const nrf_twi_mngr_t *i2c) {
  i2c_init(i2c);
  set_pwm_frequency(1600);
}

